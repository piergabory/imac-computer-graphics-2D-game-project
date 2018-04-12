#include "../include/sprites.h"

#define SPRITES_COUNT 2
#define TEXTURE_FILE "textures.png"
#define TEXTURE_COL 8
#define TEXTURE_ROW 8

static GLuint spritesGlus;

/* DRAW SPRITE
 * ===========
 *
 * Prints a sprite on the screen.
 */
void drawSprite(const unsigned int spriteindex) {
    glCallList(spritesGlus + spriteindex);
}



/* INIT SPRITE GLUS
 * ================
 * @return status boolean.
 *
 * Handles texture loading and GL list compiling. Prepare sprite list.
 */

int initSprites() {
    SDL_Surface* image = NULL;
    GLuint texId;
    
    /*~~~~~~~Texture loading~~~~~~~*/
    // image data loading
    if((image = (SDL_Surface*)IMG_Load(TEXTURE_FILE)) == NULL){
        printf(ERR_FILE_OPEN, TEXTURE_FILE);
        return 0;
    }
    
    // configure texture
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
    
    // set texture coordinates variables
    float textureWidth = 1.0/TEXTURE_COL;
    float textureHeight = 1.0/TEXTURE_ROW;
    float textureX = 0, textureY = 0;
    
    // free image data
    SDL_FreeSurface(image);
    
    
    /*~~~~~~~GLu Lists~~~~~~~*/
    // init lists
    spritesGlus = glGenLists(SPRITES_COUNT);
    
    // for each textures
    for (int i = 0; i < SPRITES_COUNT; i++) {
        // move to the texture location
        textureX = i * textureWidth;
        textureY = i / TEXTURE_COL * textureHeight;
        
        // init glu list
        glNewList(spritesGlus + i,GL_COMPILE);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texId);
        glBegin(GL_QUADS);
        
        // drawing a square:
        // vertex and their matching texture coordinates
        glTexCoord2f(textureX + textureWidth, textureY + textureHeight);
        glVertex2f(0.5, 0.5);
        
        glTexCoord2f(textureX, textureY + textureHeight);
        glVertex2f(-0.5, 0.5);
        
        glTexCoord2f(textureX, textureY);
        glVertex2f(-0.5, -0.5);
        
        glTexCoord2f(textureX + textureWidth, textureY);
        glVertex2f(0.5, -0.5);
        
        // close list
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        glEndList();
    }
    
    return 1;
}
