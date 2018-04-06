#ifndef frameworks_h
#define frameworks_h

// MacOS
#ifdef MacOS
    #include <SDL2/SDL.h>

    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLKit/GLKMatrix4.h>

// Linux
#else
    #include <SDL2/SDL.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#endif /* frameworks_h */
