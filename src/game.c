#include "../include/game.h"

Game *initGame() {
    Game *gm;
    
    gm = allocGame();
    
    // set player
    gm->player->px = 0;
    gm->player->py = 0;
    gm->player->vx = 0;
    gm->player->vy = 0;
    
    gm->player->type = PLAYER;
    gm->player->next = NULL;
    
    // set level, ennemies and bonuses
    if(loadWorld("map.ppm", gm) != 0){
        printf(ERR_LOADWORLD);
        return NULL;
    }
    
    // set projectiles
    gm->projectiles = NULL;
    
    return gm;
}

void updateGame(Game *gm) {
    gm->level->progress += 0.1;
    
    updatePlayer(gm->player);
    
    Mob *current = gm->enemies;
    while (current != NULL) {
        updateEnnemy(current);
        current = current->next;
    }
    
    current = gm->projectiles;
    while (current != NULL) {
        updateProjectile(current);
        current = current->next;
    }
}

void changeXYSpeedBy(Mob *player, float vx, float vy) {
    if (fabs(player->vx + vx) < MAX_SPEED) player->vx += vx;
    if (fabs(player->vy + vy) < MAX_SPEED) player->vy += vy;
}


#define PPM_MAGIC_NUM "P6"
#define OTHER_PPM_MAGIC_NUM "P3"
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
    
    if(strcmp(PPM_MAGIC_NUM, buff) && strcmp(OTHER_PPM_MAGIC_NUM, buff)) {
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
