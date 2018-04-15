#include "../include/events.h"

/* EVENT LOOP
 * ----------
 * SDL event loop handler
 * Asks SDL for any events and handles them accordingly
 *
 * - QUIT: set loopStatus to 0 so the main loop stops and the program ends.
 * - WINDOW IS RESIZED: collects new width and height and update the window (see window.h)
 */
int eventLoop() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) switch(e.type) {
        case SDL_QUIT:
                return 0;
            break;
            
        case SDL_KEYDOWN :
            switch (e.key.keysym.sym) {
                case SDLK_SPACE:
                    playerShoot();
                    break;
                    
                case SDLK_z: case SDLK_UP:
                    changePlayerSpeedBy(0, 0.005);
                    break;
                    
                case SDLK_s: case SDLK_DOWN:
                    changePlayerSpeedBy(0, -0.005);
                    break;
                    
                case SDLK_q: case SDLK_LEFT:
                    changePlayerSpeedBy(-0.0001, 0);
                    break;
                    
                case SDLK_d: case SDLK_RIGHT:
                    changePlayerSpeedBy(0.0001, 0);
                    break;
            }
            break;
            
        case SDL_WINDOWEVENT:
            if(e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
                WINDOW_WIDTH = e.window.data1;
                WINDOW_HEIGHT = e.window.data2;
                updateViewport();
            }
            break;
            
        default: break;
    }
    return 1;
}
