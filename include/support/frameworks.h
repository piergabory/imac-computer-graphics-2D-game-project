#ifndef frameworks_h
#define frameworks_h

// Loads librairies correctly according to the OS

// MacOS
#ifdef MacOS
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>

    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLKit/GLKMatrix4.h>

// Linux
#else
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>

    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#endif /* frameworks_h */
