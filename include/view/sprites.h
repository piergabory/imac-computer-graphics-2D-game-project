#ifndef sprites_h
#define sprites_h

#include "support/frameworks.h"
#include "support/messages.h"

#define TEXTURE_FILE "textures.png"
#define TEXTURE_COL 8
#define TEXTURE_ROW 8

#define SPRITE_WALL 0

#define SPRITE_PROJECTILE 18
#define SPRITE_PLAYER 19
#define SPRITE_BONUS 20
#define SPRITE_ENEMY 21

#define SPRITES_COUNT 23

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
