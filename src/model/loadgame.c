#include "model/loadgame.h"

/* LOAD WORLD DATA
 * ===============
 * @params: world-data file (.ppm) and references to an empty world, and moblists
 * @return: 0 if successful, other value if failed
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
        return 1;
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
    
    
    // check for file type
    char buff[32];
    if(fscanf(in,"%s",buff) == EOF) {
        printf(ERR_FILE_END, path);
        return 3;
    };
    
    if(strcmp(PPM_TYPE_1, buff) && strcmp(PPM_TYPE_2, buff)) {
        printf(ERR_FILE_FORMAT, path);
        return 2;
    }
    
    
    // read metadata (image width/height, max pixel value)
    unsigned int max = 1, width, height;
    if(fscanf(in, "%d %d %d", &width, &height, &max) == EOF) {
        printf(ERR_FILE_END, path);
        return 3;
    };
    
    gm->level = allocLevel(width, height);
    
    
    // read data
    unsigned int r = 0, g = 0, b = 0;
    MobList tmp;
    
    for (unsigned int y = 0; y < height; y++)
        for (unsigned int x = 0; x < width; x++){
            // get pixel
            if(fscanf(in, "%d %d %d", &r, &g, &b) == EOF) {
                printf(ERR_FILE_END, path);
                return 3;
            };
            
            // empty space
            if (r == max && b == max && g == max) continue;
            
            // obstacle
            gm->level->map[y][x] = (g == 0 && b == 0)? r : 0;
            
            // enemy
            if (b == 0 && r == 0) {
                if ((tmp = allocMob(ENEMY, x/(float) width, y/(float) height))!= NULL){
                    tmp->next = gm->enemies;
                    gm->enemies = tmp;
                }
                else return 3;
            }
            
            // bonus
            if (g== 0 && r == 0) {
                if ((tmp = allocMob(BONUS, x/(float) width, y/(float) height))!= NULL) {
                    tmp->next = gm->bonuses;
                    gm->bonuses = tmp;
                }
                else return 3;
            }
        }
    
    fclose(in);
    return 0;
}

