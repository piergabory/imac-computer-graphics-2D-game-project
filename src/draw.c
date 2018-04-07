#include "../include/draw.h"
World obstacleMap;
/* DRAW LOOP
 * ---------
 * OpenGL code executed between each clearBuffer and swapBuffer.
 */
static void draw() {
    glPushMatrix();
    glScalef(1.0/obstacleMap.width, 1.0/obstacleMap.height, 1.0);
    
    glPushMatrix();
    glTranslatef(-(obstacleMap.progress+=0.001),0,0);
    drawTerrain(obstacleMap);
    glPopMatrix();
    
    glTranslatef(player.xpos, obstacleMap.height + player.ypos * 0.5,0);
    drawSprite(SPRITE_PLAYER);
    /*
        DRAWING CODE GOES HERE
     */
    
    glPopMatrix();
}




// framerate (minimum delay before the return of a loop call)
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

// tells weather the main loop shall continue or not
static int loopStatus = 1;




/* EVENT LOOP
 * ----------
 * SDL event loop handler
 * Asks SDL for any events and handles them accordingly
 *
 * - QUIT: set loopStatus to 0 so the main loop stops and the program ends.
 * - WINDOW IS RESIZED: collects new width and height and update the window (see window.h)
*/
static void eventLoop() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) switch(e.type) {
        case SDL_QUIT:
            loopStatus = 0;
            break;
            
        case SDL_KEYDOWN :
            switch (e.key.keysym.sym) {
                case SDLK_SPACE:
                    printf("bang!\n");
                    break;
                    
                case SDLK_z: case SDLK_UP:
                    movePlayer(1);
                    break;
                    
                case SDLK_s: case SDLK_DOWN:
                    movePlayer(-1);
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
}




/* LOOP
 * ----
 * Main SDL Loop
 * @param: SDL window, see window.h
 *
 * - tracks time
 * - clears the screen with clearing color (set in draw.h)
 * - calls draw
 * - starts event loop
 * - swap buffers
 * - wait for the next frame before returning
 */
static int loop(SDL_Window *win) {
    Uint32 startTime = SDL_GetTicks();
    glClear(GL_COLOR_BUFFER_BIT);
    
    // execute draw
    draw();
    
    // manages events
    eventLoop();
    
    // swap window
    SDL_GL_SwapWindow(win);
    
    // wait
    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
        SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
    
    return loopStatus;
}




/* START LOOP
 * ----------
 * Initialise and launch main loop, begining drawing and event tracking operations
 *
 * @param: sdl window (see window.h)
 *
 * the loop method is called until it returns false (0)
 */
void startLoop(SDL_Window *win) {
    // set sky color
    glClearColor(0.5, /*blue:*/ 0.7, /*green:*/ 1.0, /*alpha:*/ 1.0);
    
    // enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (loop(win));
}
