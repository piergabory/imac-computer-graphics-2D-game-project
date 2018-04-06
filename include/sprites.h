#ifndef sprites_h
#define sprites_h

#include "../include/frameworks.h"
#include "../include/flapimac.h"

/* GET SPRITE GLU
 * ==============
 * @param file path to a .png file (texture of the sprite)
 * @return OpenGL list. When called, draws a textured square.
 *
 * Handles texture loading and GL list compiling.
 */
GLuint getSpriteGlu(char *file);

#endif /* sprites_h */
