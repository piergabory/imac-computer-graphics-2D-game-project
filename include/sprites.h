#ifndef sprites_h
#define sprites_h

#include "frameworks.h"
#include "messages.h"

#define SPRITE_WALL 0
#define SPRITE_PLAYER 1

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
