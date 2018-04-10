#include "../include/game.h"

#define MAX_SPEED 1
#define DRAG 0.95

Game *initGame() {
    Game *gm;
    
    gm = (Game *) malloc(sizeof(Game));
    
    gm->level = (Level *) malloc(sizeof(Level));
    gm->enemies = (MobList*) malloc(sizeof(MobList));
    gm->bonuses = (MobList*) malloc(sizeof(MobList));
    gm->player = (Mob*) malloc(sizeof(Mob));
    
    // set player
    gm->player->px = 0;
    gm->player->py = 0;
    gm->player->vx = 0;
    gm->player->vy = 0;
    
    gm->player->type = PLAYER;
    gm->player->next = NULL;
    
    // set world
    loadWorld("image.ppm", gm);
    gm->level->progress = 0;
    
    return gm;
}

void updateGame(Game *gm) {
    // position
    gm->player->px += gm->player->vx;
    gm->player->py += gm->player->vy;
    
    // drag
    gm->player->vx *= DRAG;
    gm->player->vy *= DRAG;
    
    
    // bounce on borders
    if (gm->player->px > 1 || gm->player->px < 0) {
        gm->player->vx *= -1;
        gm->player->px = roundf(gm->player->px);
    }
    
    if (gm->player->py > 1 || gm->player->py < 0) {
        gm->player->vy *= -1;
        gm->player->py = roundf(gm->player->py);
    }
}

void changeXYSpeedBy(Mob *player, float vx, float vy) {
    if (fabs(player->vx + vx) < MAX_SPEED) player->vx += vx;
    if (fabs(player->vy + vy) < MAX_SPEED) player->vy += vy;
}


MobList allocMob(unsigned char type, float x, float y) {
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



#define PPM_MAGIC_NUM "P6"

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
    if(fscanf(in, "%d %d %d", &(gm->level->width), &(gm->level->height), &max) == EOF) {
        printf(ERR_FILE_END, path);
        return 3;
    };
    
    // allocate memory
    // obstacle map rows
    gm->level->map = (int**)calloc(gm->level->width, sizeof(int*));
    if (gm->level->map == NULL) {
        printf(ERR_MALLOC);
        return 4;
    }
    
    
    // read data
    unsigned int r = 0, g = 0, b = 0;
    
    for (int x = 0; x < gm->level->width; x++){
        
        // allocate memory for obstacle map columns
        gm->level->map[x] = (int*)calloc(gm->level->height, sizeof(int));
        if (gm->level->map == NULL) {
            printf(ERR_MALLOC);
            return 4;
        }
        
        for (int y = 0; y < gm->level->height; y++) {
            // get pixel
            if(fscanf(in, "%d %d %d", &r, &g, &b) == EOF) {
                printf(ERR_FILE_END, path);
                return 3;
            };
            
            // obstacle
            gm->level->map[x][y] = r;
            
            // enemy
            if (r == 0 && g == max && b == 0) {
                if ((*(gm->enemies) = allocMob(ENEMY, x, y))!= NULL)
                    gm->enemies = &(*(gm)->enemies)->next;
                else return 3;
                
            }
            
            // bonus
            if (r == 0 && g == 0 && b == max) {
                if ((*(gm->bonuses) = allocMob(BONUS, x, y))!= NULL)
                    gm->bonuses = &(*(gm)->bonuses)->next;
                else return 3;
            }
        }
    }
    return 0;
}
