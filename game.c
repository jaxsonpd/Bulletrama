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

#define PACER_FREQ 200

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
void destroyWalls(uint8_t walls[MAX_Y + 1][MAX_X + 1], Bullet_t bullets[], uint8_t numBullets) {
    // Loop through Bullets checking walls
    for (uint8_t i = 0; i < numBullets; i++) {
        if (bullets[i].y != 10 && bullets[i].owner == -1) { // Active enemy bullet
            if (walls[bullets[i].y][bullets[i].x] == 1) { // Only destroy if wall is there
                walls[bullets[i].y][bullets[i].x] = 0; // Delete wall
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
void destroyBullet(Bullet_t bullets[10], uint8_t numBullets) {
    for (uint8_t arrPos=0; arrPos < numBullets; arrPos++) {
        for (uint8_t i= arrPos; i < numBullets; i++) {
            if (arrPos != i && bullets[arrPos].x == bullets[i].x  &&  bullets[arrPos].y == bullets[i].y) {
                bullets[arrPos].y=10;
                bullets[i].y = 10;
            }    
        }
    }
}

int main(void) {
    // Initialise the controller
    system_init();
    initGameBoard();
    ir_uart_init();
    pacer_init(PACER_FREQ);
    
    // Configure sprites
    bulletConfig(L1_BULLET_SPEED);
    playerConfig(L1_MOVE_SPEED, L1_START_HEALTH, L1_MAX_HEIGHT);

    // Initialise the player
    Player_t player = playerInit(0, 0);

    // Initialise the bullets
    uint8_t numBullets = 10;

    Bullet_t bullets[numBullets] = {0};

    for (uint8_t i = 0; i < numBullets; i++)
    {
        bullets[i] = bulletInit(0, 10, 1);
    }
    
    // Initialise the timers
    uint16_t bulletDelay = 0;
    uint16_t bulletUpdateDelay = 0;

    // Initialise the walls
    uint8_t walls[MAX_Y + 1][MAX_X + 1] = {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0}
    };
    
    // Tracking variables
    bool hasInput = false;
    char input = 0;
    
    // Start the main loop
    while (!gameOver) {
        // Pacer Wait
        pacer_wait();

        //Nav update
        navswitch_update();
        
        // Player Position update
        playerUpdate(&player);

        // Get new IR info
        if (ir_uart_read_ready_p()) {
            input = ir_uart_getc();
            hasInput = true;
        }

        // Add new bullets from IR and player 
        // Add new bullet at player postion if needed
        if (player.hasFired && player.canFire) {
            uint8_t i = 0;
            bool found_empty = false;

            while (i < numBullets && !found_empty) {
                if(bullets[i].y == 10) {
                    bullets[i] = bulletInit(player.x, player.y + 1, 1);
                    found_empty = true;
                }
                i ++;
            }
            
            // Reset player 
            player.hasFired = false;
            bulletDelay = 0;
        }

        // Add IR bullets
        if (hasInput && input >= 'A' && input <= 'G' ) {
            bullets[0] = bulletInit(('G' - input) - 'A', 4, -1);
        }

        // Send IR bullets and remove bullets that have left the screen
        uint8_t i = 0;

        while (i < numBullets) {
            if(bullets[i].y == 5) { // Send bullet
                bullets[i].y = 10; // Delete bullet

                // Send IR postion
                ir_uart_putc('A' + bullets[i].x);
            }

            if (bullets[i].y == -1) { // Bullet off screen
                bullets[i].y = 10; // Delete bullet
            }

            i ++;
        }

        // Update walls if bullet has hit them
        destroyWalls(walls, bullets, numBullets);

        // Update bullets if bullet hits bullet
        destroyBullet(bullets, numBullets);
        

        // Check for health and game over
        // Check to see if a enemy bullet is on player postion

        // Update player health if so

        if (player.health == 0) {
            gameOver = true;
            won = false;

            // tell there board they have won
        } 
        
        // Reset player fire delay if it is time to
        if (!(player.canFire) && bulletDelay > L1_BULLET_FIRE_DELAY) {
            player.canFire = true;
        }

        // Update bullet postion if it is time to
        if (bulletUpdateDelay > L1_BULLET_UPDATE_WAIT) {
            // Update bullets
            bulletUpdate(bullets);

            bulletUpdateDelay = 0;
        }

        // Update the game board
        displayGameBoard(&player, bullets, walls, numBullets);

        // Update timers
        bulletDelay += !(player.canFire) ? 1 : 0;
        bulletUpdateDelay ++;
        hasInput = false;
    }
}

