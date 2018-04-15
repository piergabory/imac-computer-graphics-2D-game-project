#ifndef sprites_h
#define sprites_h

#include "frameworks.h"
#include "messages.h"

#define SPRITE_WALL 0
#define SPRITE_PLAYER 1
#define SPRITE_ENEMY 2
#define SPRITE_BONUS 3
#define SPRITE_PROJECTILE 4

#define SPRITE_CORNER_TOP_LEFT 5
#define SPRITE_CORNER_TOP_RIGHT 6
#define SPRITE_CORNER_BOTTOM_LEFT 7
#define SPRITE_CORNER_BOTTOM_RIGHT 8

#define SPRITES_COUNT 9

/* INIT SPRITES
 * ============
 * @return status boolean.
 *
 * Handles texture loading and GL list compiling. Prepare sprite list.
 */
int initSprites();


/* DRAW SPRITE
 * ===========
 *
 * Prints a sprite on the screen.
 */
void drawSprite(const unsigned int spriteindex);


#endif /* sprites_h */
