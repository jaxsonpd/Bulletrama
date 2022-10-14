/**
 * @file game.c
 * @brief The main excution file for the game
 * @author Jack Duignan and Ben Gunn.
 * @date 2022-10-03
 */

/**
 * Main flow of the game
 * 1. Initialise the game
 * 2. Start the game loop
 * 3. update the player information
 * 4. update the enemy information (IR)
 * 5. update the bullet information
 * 6. check for collisions
 * 7. check for game over
 * 6. update the screen
 * 7. repeat
 */

#include "player.h"
#include "game.h"
#include "system.h"
#include "gameDisplay.h"
#include "navswitch.h"
#include "bullet.h"
#include "pacer.h"
#include "ir_uart.h"
#include "levels.h"
#include "button.h"

// Constants
#define PACER_FREQ 200
#define TEXT_SCROLL_RATE 20

// Global Variables
uint8_t level = 1;
bool gameOver = false;
bool won = true;
bool pause = false;

/** Destroy walls if bullets have hit them
 * 
 * @param walls an array of walls
 * @param bullets an array of bullets
 * @param numBullets the number of bullets
*/
void destroy_walls(uint8_t walls[MAX_Y + 1][MAX_X + 1], Bullet_t bullets[], uint8_t numBullets) {
    // Loop through Bullets checking walls
    for (uint8_t i = 0; i < numBullets; i++) {
        if (bullets[i].y != 10 && bullets[i].owner == -1) { // Active enemy bullet
            if (walls[MAX_Y - bullets[i].y][bullets[i].x] == 1) { // Only destroy if wall is there
                walls[MAX_Y - bullets[i].y][bullets[i].x] = 0; // Delete wall
                bullets[i].y = 10; // Delete bullet
            }
        }
    }
}

/** Destroy bullets if they hit each other
 * 
 * @param bullets array of bullets
 * @param numBullets Numbber of bullets possible in array
 */
void destroy_bullet(Bullet_t bullets[10], uint8_t numBullets) {
    for (uint8_t arrPos=0; arrPos < numBullets; arrPos++) {
        for (uint8_t i= arrPos; i < numBullets; i++) {
            if (arrPos != i && bullets[arrPos].x == bullets[i].x  &&  bullets[arrPos].y == bullets[i].y) {
                // Delete the two bullets
                bullets[arrPos].y = 10;
                bullets[i].y = 10;
            }    
        }
    }
}

/** Clean up the bullet array sending any that are at the top of the screen.
 * 
 * @param bullets an array of bullets
 * @param numBullets the number of bullets
 */
void clean_and_send_bullets(Bullet_t bullets[], uint8_t numBullets) {
    uint8_t i = 0;

    while (i < numBullets) {
        if(bullets[i].y == MAX_Y + 1) { // Bullet at the top the screen
            // Send IR postion
            ir_uart_putc('A' + bullets[i].x);
        }

        if (bullets[i].y == -1 || bullets[i].y == MAX_Y + 1) { // Bullet off screen
            bullets[i].y = 10; // Delete bullet
        }

        i ++;
    }
}

/** Check to see if the player needs to update health
 * 
 * @param player a pointer to a player struct
 * @param bullets an array of bullets
 * @param numBullets the number of bullets
 */
void update_health(Player_t* player, Bullet_t bullets[], uint8_t numBullets) {
        // Check to see if a enemy bullet is on player postion
        for (uint8_t i = 0; i < numBullets; i++) {
            if (bullets[i].y == player->y && bullets[i].x == player->x && bullets[i].owner == -1) {
                player->health --;
                bullets[i].y = 10; // Delete bullet
            }
        }

        // If player health is 0 then game over
        if (player->health == 0) {
            gameOver = true;
            won = false;
        } 
}

/** Initialise the game for level 1
 * 
 */

void level_1_init(void) {
    // Configure items
    bullet_config(L1_BULLET_SPEED);
    player_config(L1_MOVE_SPEED, L1_START_HEALTH, L1_MAX_HEIGHT);
}

/** Play the game
 * 
 */
void play_game(Player_t player, uint8_t walls[MAX_Y + 1][MAX_X + 1], Bullet_t bullets[], uint8_t numBullets) {
     // Tracking variables
    bool hasInput = false;
    char input = 0;

    // Initialise the timer variables
    uint16_t bulletDelay = 0;
    uint16_t bulletUpdateDelay = 0;

    // Start the main loop
    while (!gameOver) {
        // Pacer Wait
        pacer_wait();

        //Nav update
        navswitch_update();

        // Button update
        button_update();
        
        // Player Position update
        player_update(&player);

        // Get new IR info
        if (ir_uart_read_ready_p()) {
            input = ir_uart_getc();
            hasInput = true;
        }

        // Add new bullets from IR and player 
        // Add new bullet at player postion if needed
        if (player.hasFired && player.canFire) {
            bullet_add(bullets, numBullets, bullet_init(player.x, player.y + 1, 1));
            
            // Reset player 
            player.hasFired = false;
            bulletDelay = 0;
        }

        // Add IR bullets
        if (hasInput && input >= 'A' && input <= 'G' ) {
            bullet_add(bullets, numBullets, bullet_init('A' - input + MAX_X, MAX_Y, -1));
        }

        // Send IR bullets and remove bullets that have left the screen
        clean_and_send_bullets(bullets, numBullets);

        // Update walls if bullet has hit them
        destroy_walls(walls, bullets, numBullets);

        // Update bullets if bullet hits bullet
        destroy_bullet(bullets, numBullets);
        
        // Check for health and game over
        update_health(&player, bullets, numBullets);

        // Has the player won
        if (gameOver && !won) {
            // tell the other board that they won
            ir_uart_putc('W');
        }

        // Has the player lost
        if (hasInput && input == 'W') {
            gameOver = true;
            won = true;
        }
        
        // Reset player fire delay if it is time to
        if (!(player.canFire) && bulletDelay > L1_BULLET_FIRE_DELAY) {
            player.canFire = true;
        }

        // Update bullet postion if it is time to
        if (bulletUpdateDelay > L1_BULLET_UPDATE_WAIT) {
            // Update bullets
            bullet_update(bullets);
            bulletUpdateDelay = 0;
        }

        // Check pause
        if (button_push_event_p(0)) {
            ir_uart_putc('P');
            display_pause();
        }
        
        if (hasInput && input == 'P') {
            display_pause();
        }

        // Update the game board
        display_game_board(&player, bullets, walls, numBullets);

        // Update timers
        bulletDelay += !(player.canFire) ? 1 : 0;
        bulletUpdateDelay ++;
        hasInput = false;
    }
}

int main(void) {
    // Initialise the controller
    system_init();
    init_game_board(PACER_FREQ, TEXT_SCROLL_RATE);
    ir_uart_init();
    pacer_init(PACER_FREQ);
    button_init();
    
    while (1) {
        // Initialise the walls as an empty array
        uint8_t walls[MAX_Y + 1][MAX_X + 1];
        
        // Get the level
        level = get_level();

        // Initialise the level
        if (level == 1) {
            level_1_init();

            uint8_t walls[MAX_Y + 1][MAX_X + 1] = {
                {0, 0, 0, 0, 0, 0, 0},
                {1, 1, 1, 1, 1, 1, 1},
                {0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
            };
        }

        // Clear game objects
        // Initialise the player
        Player_t player = player_init(0, 0);

        // Initialise the bullets
        uint8_t numBullets = MAX_BULLETS;

        Bullet_t bullets[MAX_BULLETS];

        // Populate the bullet array with empty bullets
        for (uint8_t i = 0; i < numBullets; i++) {
            bullets[i] = bullet_init(0, 10, 1);
        }

        // Play the level
        play_game(player, walls, bullets, numBullets);

        // Display the game over screen and who won
        game_over();

        if (won) {
            game_win();
        } else {
            game_loss();
        }

        // Reset the golbal variables
        gameOver = false;
        won = true;
    }
    
    

    
}

