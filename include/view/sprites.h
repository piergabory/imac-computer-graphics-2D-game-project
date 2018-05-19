#ifndef sprites_h
#define sprites_h

#include "support/messages.h"
#include "support/window.h"
#include "model/structs/mob.struct.h"

// texture file path
#define TEXTURE_FILE "textures.png"

// texture grid dimentions
#define TEXTURE_COL 8
#define TEXTURE_ROW 22

// screen values in texture grid cells
#define SCREEN_BEGIN 4 // row after which screens begin
#define SCREEN_WIDTH 8 
#define SCREEN_HEIGHT 6

#define SCREEN_COUNT 3

// texture indexes
// a entity can have multiple sprites next to each other
typedef enum {
    SPRITE_WALL = 0,
    SPRITE_PROJECTILE = 18,
    SPRITE_PLAYER,
    SPRITE_BONUS = 21,
    SPRITE_ENEMY = 24,
    SPRITE_ENEMY_PROJECTILE = 26
} Sprite;

// Sprite alternatives count
typedef enum {
    ALT_WALL = 6,
    ALT_PLAYER = 2,
    ALT_BONUS = 1,
    ALT_ENEMY = 2,
    ALT_PROJECTILE = 1,
    ALT_ENEMY_PROJECTILE = 1
} SpriteAlt;

typedef enum {
    SCREEN_GAME_OVER,
    SCREEN_LEVEL_COMPLETE,
    SCREEN_PRESS_SPACEBAR
} Screen;

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
void drawSprite(Sprite index);
void drawScreen(Screen index);

/**
 * Get sprite id from mobtype
 */
void getSprite(MobType type, Sprite *, SpriteAlt *);

/**
 * Sprite lists array
 * Static @var GLuint sptiresGlus
 */
static GLuint spritesGlus;
static GLuint screenGlus;

#endif /* sprites_h */
