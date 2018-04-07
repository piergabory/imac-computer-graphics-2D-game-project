#include "../include/load.h"
#include "../include/messages.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PPM_MAGIC_NUM "P6"

static MobList allocMob(unsigned char type, float x, float y) {
    MobList new = (MobList)malloc(sizeof(Mob));
    if (new == NULL) {
        printf(ERR_MALLOC);
        return NULL;
    }
    
    new->px = x;
    new->py = y;
    new->type = type;
    new->next = NULL;
    
    return new;
}




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

int loadWorld(char* path, Level *l, MobList *enemy, MobList *bonus) {
    // TODO : Discard comments
    
    // attempts to open file
    FILE *in = NULL;
    if ((in = fopen(path,"r")) == NULL) {
        printf(ERR_FILE_OPEN, path);
        return 1;
    };
    
    
    // check for file type
    char buff[32];
    if(fscanf(in,"%s",buff) == EOF) {
        printf(ERR_FILE_END, path);
        return 3;
    };
    
    if(strcmp(PPM_MAGIC_NUM, buff)) {
        printf(ERR_FILE_FORMAT, path);
        return 2;
    }
    
    
    // read metadata (image width/height, max pixel value)
    unsigned int max = 1;
    if(fscanf(in, "%d %d %d", &(l->width), &(l->height), &max) == EOF) {
        printf(ERR_FILE_END, path);
        return 3;
    };
    
    // allocate memory
    // obstacle map rows
    l->map = (int**)calloc(l->width, sizeof(int*));
    if (l->map == NULL) {
        printf(ERR_MALLOC);
        return 4;
    }
    
    
    // read data
    unsigned int r = 0, g = 0, b = 0;
    
    for (int x = 0; x < l->width; x++){
        
        // allocate memory for obstacle map columns
        l->map[x] = (int*)calloc(l->height, sizeof(int));
        if (l->map == NULL) {
            printf(ERR_MALLOC);
            return 4;
        }
        
        for (int y = 0; y < l->height; y++) {
            // get pixel
            if(fscanf(in, "%d %d %d", &r, &g, &b) == EOF) {
                printf(ERR_FILE_END, path);
                return 3;
            };

            // obstacle
            l->map[x][y] = r;

            // enemy
            if (r == 0 && g == max && b == 0) {
                if ((*enemy = allocMob(ENEMY, x, y))!= NULL)
                    enemy = &(*enemy)->next;
                else return 3;
                
            }
            
            // bonus
            if (r == 0 && g == 0 && b == max) {
                if ((*bonus = allocMob(BONUS, x, y))!= NULL)
                    bonus = &(*bonus)->next;
                else return 3;
            }
        }
    }
    return 0;
}
