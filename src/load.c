#include "../include/load.h"
#include "../include/messages.h"

#define PPM_MAGIC_NUM "P6"

static MobList allocMob(unsigned char type, float x, float y) {
    MobList new = (MobList)malloc(sizeof(Mob));
    if (new == NULL) {
        printf(ERR_MALLOC);
        return NULL;
    }
    
    new->xpos = x;
    new->ypos = y;
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

int loadWorld(char* path, World *w, MobList *enemy, MobList *bonus) {
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
    if(fscanf(in, "%d %d %d", &(w->width), &(w->height), &max) == EOF) {
        printf(ERR_FILE_END, path);
        return 3;
    };
    
    // allocate memory for the obstacle data
    w->data = (int*)malloc(w->width * w->height * sizeof(int));
    if (w->data == NULL) {
        printf(ERR_MALLOC);
        return 4;
    }
    
    
    // read data
    unsigned int r = 0, g = 0, b = 0;
    
    for (int x = 1; x <= w->width; x++)
    for (int y = 1; y <= w->height; y++) {
        // get pixel
        if(fscanf(in, "%d %d %d", &r, &g, &b) == EOF) {
            printf(ERR_FILE_END, path);
            return 3;
        };

        // obstacle
        w->data[x*y-1] = (r > 0) ? 0:1;
        
        // enemy
        if (g > 0) {
            if ((*enemy = allocMob(MOB_TYPE_ENEMY, x, y))!= NULL)
                enemy = &(*enemy)->next;
            else return 3;
                
        }
        
        // bonus
        if (b > 0) {
            if ((*bonus = allocMob(MOB_TYPE_BONUS, x, y))!= NULL)
                bonus = &(*bonus)->next;
            else return 3;
                
        }

    }
    
    return 0;
}
