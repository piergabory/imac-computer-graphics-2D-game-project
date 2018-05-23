#include "view/sprites.h"

/**
 * DRAW SPRITE
 * -----------
 *
 * Prints a sprite on the screen.
 */
void drawSprite(Sprite index) {
    glCallList(spritesGlus + index);
}

void drawScreen(Screen index) {
    glCallList(screenGlus + index);
}

void getSprite(MobType type, Sprite *s, SpriteAlt *a) {
    switch (type) {
        case ENEMY:
            *s = SPRITE_ENEMY;
            *a = ALT_ENEMY;
            break;
            
        case BONUS_HEALTH:
            *s = SPRITE_BONUS_HEALTH;
            *a = ALT_BONUS;
            break;
            
        case BONUS_WEAPON:
            *s = SPRITE_BONUS_WEAPON;
            *a = ALT_BONUS;
            break;
            
        case BONUS_SPEED:
            *s = SPRITE_BONUS_SPEED;
            *a = ALT_BONUS;
            break;
            
        case PLAYER:
            *s = SPRITE_PLAYER;
            *a = ALT_PLAYER;
            break;
            
        case PROJECTILE:
            *s = SPRITE_PROJECTILE;
            *a = ALT_PROJECTILE;
            break;
            
        case ENEMY_PROJECTILE:
            *s = SPRITE_ENEMY_PROJECTILE;
            *a = ALT_ENEMY_PROJECTILE;
            break;
    }
}

/**
 * INIT SPRITES
 * ------------
 * Handles texture loading and GL list compiling. Prepare sprite list.
 *
 * @return status boolean.
 */
int initSprites() {
    // init vars
    SDL_Surface* image = NULL;
    GLuint texId;
    
    
    ////// Load texture
    
    // image data loading
    image = (SDL_Surface*) IMG_Load(TEXTURE_FILE);
    if(image == NULL){
        printf(ERR_FILE_OPEN, TEXTURE_FILE);
        return 0;
    }
    
    // configure texture (transparent png)
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, image->pixels);
    
    // free image data
    SDL_FreeSurface(image);


    ////// prepare GLU lists

    // init texture coordinates variables
    float textureWidth = 1.0/TEXTURE_COL;
    float textureHeight = 1.0/TEXTURE_ROW;
    float textureX = 0, textureY = 0;
    
    // init lists
    spritesGlus = glGenLists(SPRITES_COUNT);
    
    // for each sprite of the texture file
    for (int i = 0; i < SPRITES_COUNT; i++) {
        // move to the texture location
        textureX = i * textureWidth;
        textureY = i / TEXTURE_COL * textureHeight;
        
        // init glu list
        glNewList(spritesGlus + i,GL_COMPILE);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texId);
        glBegin(GL_QUADS);
        
        // drawing a square and apply the sprite:
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
    } /* end for */
    
    
    float screenWidth = SCREEN_WIDTH * textureWidth;
    float screenHeight = SCREEN_HEIGHT * textureHeight;
    float screenBegin = SCREEN_BEGIN * textureHeight;

    // init lists
    screenGlus = glGenLists(SCREEN_COUNT);
    
    // for each sprite of the texture file
    for (int i = 0; i < SCREEN_COUNT; i++) {
        
        // init glu list
        glNewList(screenGlus + i,GL_COMPILE);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texId);
        glBegin(GL_QUADS);
        
        // drawing a square and apply the sprite:
        // vertex and their matching texture coordinates
        glTexCoord2f(screenWidth, screenHeight * (i+1) + screenBegin);
        glVertex2f(1,1);
        
        glTexCoord2f(0, screenHeight * (i+1) + screenBegin);
        glVertex2f(0,1);
        
        glTexCoord2f(0, screenHeight * i + screenBegin);
        glVertex2f(0,0);
        
        glTexCoord2f(screenWidth, screenHeight * i + screenBegin);
        glVertex2f(1, 0);
        
        // close list
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        glEndList();
    } /* end for */
    
    // return success
    return 1;
}
