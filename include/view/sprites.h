#ifndef sprites_h
#define sprites_h

#include "support/frameworks.h"
#include "support/messages.h"

#define TEXTURE_FILE "textures.png"
#define TEXTURE_COL 8
#define TEXTURE_ROW 8

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
