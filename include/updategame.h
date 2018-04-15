#ifndef updategame_h
#define updategame_h

#include <math.h>

#include "gamedata.h"

#define MAX_SPEED 1
#define DRAG 0.99

void updatePlayer(Mob *p);
void updateEnnemy(Mob *e);
void updateProjectile(Mob *p);

#endif /* updategame_h */
