#include "../include/sprites.h"
#include "../include/messages.h"


/* GET SPRITE GLU
 * ==============
 * @param file path to a .png file (texture of the sprite)
 * @return OpenGL list. When called, draws a textured square.
 *
 * Handles texture loading and GL list compiling.
 */

// TODO ? : Load one spritesheet instead of a png for each sprite
 GLuint getSpriteGlu(char *file) {
    SDL_Surface* image = NULL;
    GLuint texId;
    
    /*~~~~~~~Texture loading~~~~~~~*/
    // image data loading
    if((image = (SDL_Surface*)IMG_Load(file)) == NULL){
        printf(ERR_FILE_OPEN, file);
        return 0;
    }
    
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
    
    // free image data
    SDL_FreeSurface(image);

     
    /*~~~~~~~GL List~~~~~~~*/
    GLuint newList = glGenLists(1);
    glNewList(newList,GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);
    glBegin(GL_QUADS);
    
    // drawing a square:
    // vertex and their matching texture coordinates
    glTexCoord2f(1, 1);
    glVertex2f(-1, -1);
     
    glTexCoord2f(0, 1);
    glVertex2f(1, -1);
     
    glTexCoord2f(0, 0);
    glVertex2f(1, 1);
     
    glTexCoord2f(1, 0);
    glVertex2f(-1, 1);

    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEndList();
    
    return newList;
}
