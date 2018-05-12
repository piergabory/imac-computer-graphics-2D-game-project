#include "model/loadgame.h"

/**
 * LOAD WORLD (LEVEL) DATA
 * -----------------------
 * @param String path to the world's data file (.PPM format)
 * @param Game *gm reference to the game structure to initialize
 *
 * @return 0 if successful, other value if failed
 *
 * Load a .ppm (portable pixel map) image representing different element of the game world:
 * - red pixels represent obstacles
 * - green pixels represent enemies
 * - blue pixels represent bonuses
 * Will handle the file loading, parsing and edit of the world and mobile lists
 */

int loadWorld(char *path, Game *gm) {
    
    // attempts to open file
    FILE *in = NULL, *tmpfile = NULL;
    if ((in = fopen(path,"r")) == NULL || (tmpfile = fopen(TEMP_FILE,"w")) == NULL) {
        printf(ERR_FILE_OPEN, path);
        return 1;  // error failed to open
    };
    
    
    // remove comment lines
    char keep = 1, discard = 1;
    while ((keep = fgetc(in)) != EOF && discard != EOF) {
        if (keep == PPM_COMMENT)                                // when met with a comment char '#',
            do discard = fgetc(in);                     // we skip until we arrive
            while (discard != '\n' && discard != EOF);  // at the end of the line
        else
            fputc(keep, tmpfile); // otherwise we copy the file char by char
    }
    fclose(in); fclose(tmpfile);
    in = fopen(TEMP_FILE, "r");
    system("rm "TEMP_FILE); // destroy temp file
    
    
    // check for file type (magic ppm word)
    char buff[32];
    if(fscanf(in,"%s",buff) == EOF) {
        printf(ERR_FILE_END, path);
        return 3; // error unexpected end of file
    };
    
    if(strcmp(PPM_TYPE_1, buff) && strcmp(PPM_TYPE_2, buff)) {
        printf(ERR_FILE_FORMAT, path);
        return 2; // error invalid file format
    }
    
    
    // read metadata (image width/height and max pixel value)
    unsigned int max = 1, width, height;
    if(fscanf(in, "%d %d %d", &width, &height, &max) == EOF) {
        printf(ERR_FILE_END, path);
        return 3; // error unexpected end of file
    };
    
    
    // allocate level, sized with PPM image dimentions
    gm->level = allocLevel(width, height);
    
    
    // read pixel data:
    
    unsigned int r = 0, g = 0, b = 0;
    
    for (unsigned int y = 0; y < height; y++)
        for (unsigned int x = 0; x < width; x++){
            // get pixel
            if(fscanf(in, "%d %d %d", &r, &g, &b) == EOF) {
                printf(ERR_FILE_END, path);
                return 3;  // error unexpected end of file
            };
            
            // CASE : empty space, skip to next pixel
            if (r == max && b == max && g == max) continue;
            
            // CASE : obstacle, set terrain type
            gm->level->map[y][x] = (g == 0 && b == 0) ? r/10 : 0;
            
            // CASE : enemy, allocate enemy in enemies list
            if (b == 0 && r == 0) {
                if(newMob(&(gm->enemies), ENEMY, x/(float) width, y/(float) height, 0, 0) == NULL) return 4;
            }
            
            // CASE : bonus, allocate new bonus in moblist
            if (g== 0 && r == 0) {
                if(newMob(&(gm->bonuses), BONUS, x/(float) width, y/(float) height, 0, 0) == NULL) return 4;
            }
        }
    
    // close file
    fclose(in);
    
    // return success code
    return 0;
}

