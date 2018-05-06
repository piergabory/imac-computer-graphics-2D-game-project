#ifndef updategame_h
#define updategame_h

#include <math.h>

#include "gamedata.h"

#define DRAG 0.99
#define PROGRESS_RATE 0.0003

void updatePlayer(Mob *p);
void updateEnnemy(Mob *e, Mob *p);
void updateProjectile(Mob *p);

#endif /* updategame_h */
