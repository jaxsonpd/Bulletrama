/**
 * @file player.c
 * @author Jack Duignan
 * @brief Player movement and health management functions
 * @date 2022-10-02
 */

#include "player.h"

/** Intialise the player
 * @param x x position of the player
 * @param y y position of the player
 * @param startHealth health of the player
 * @return pointer to a Player_t struct
 */
Player_t* playerInit(uint8_t x, uint8_t y, uint8_t startHealth) {
    Player_t* player = malloc(sizeof(Player_t));
    player->x = x;
    player->y = y;
    player->health = startHealth;
    player->hasFired = false;

    return player;
}

