#ifndef sprites_h
#define sprites_h

#include "support/frameworks.h"
#include "support/messages.h"

// texture file path
#define TEXTURE_FILE "textures.png"

// texture grid dimentions
#define TEXTURE_COL 8
#define TEXTURE_ROW 8

// texture indexes
// a entity can have multiple sprites next to each other
#define SPRITE_WALL 0
#define SPRITE_PROJECTILE 18
#define SPRITE_ENEMY_PROJECTILE 26
#define SPRITE_PLAYER 19
#define SPRITE_BONUS 21
#define SPRITE_ENEMY 24
#define SPRITE_DEFEAT 27
#define SPRITE_VICTORY 28
#define SPRITE_EMPTY 29

#define SPRITE_WALL_ALT_COUNT 16
#define SPRITE_PLAYER_ALT_COUNT 2
#define SPRITE_BONUS_ALT_COUNT 1
#define SPRITE_ENEMY_ALT_COUNT 2
#define SPRITE_PROJECTILE_ALT_COUNT 1
#define SPRITE_ENEMY_PROJECTILE_ALT_COUNT 1


// total sprites
#define SPRITES_COUNT 30


/**
 * INIT SPRITES
 * ------------
 * Handles texture loading and GL list compiling. Prepare sprite list.
 *
 * @return status boolean.
 */
int initSprites();


/**
 * DRAW SPRITE
 * -----------
 * Prints a sprite on the screen.
 *
 * @param const unsigned int index of the sprite.
 */
void drawSprite(const unsigned int spriteindex);


/**
 * Sprite lists array
 * Static @var GLuint sptiresGlus
 */
static GLuint spritesGlus;

#endif /* sprites_h */
