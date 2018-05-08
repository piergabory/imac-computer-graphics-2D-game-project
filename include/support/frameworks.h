#ifndef frameworks_h
#define frameworks_h

// Loads librairies correctly according to the OS

// MacOS
#ifdef MacOS
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>

    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>

    // Apple has deprecated gluOrtho2D for their OpenGL Kit framework
    #include <GLKit/GLKMatrix4.h>
    #define SET_ORTHO_MATRIX(left, right, bottom, top)  { \
            GLKMatrix4 orthoMat = GLKMatrix4MakeOrtho(left, right, bottom, top, -1.0f, 1.0f); \
            glLoadMatrixf(orthoMat.m); \
    } \

// Linux
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>

    #include <GL/gl.h>
    #include <GL/glu.h>

    #define SET_ORTHO_MATRIX(left, right, bottom, top) {gluOrtho2D(left,right,bottom,top);}
#endif

#endif /* frameworks_h */
