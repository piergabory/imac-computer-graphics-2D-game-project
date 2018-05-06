#include "model/updategame.h"

void updatePlayer(Mob *p) {
    // position
    p->px += p->vx + PROGRESS_RATE;
    p->py += p->vy;
    
    // drag
    p->vx *= DRAG;
    p->vy *= DRAG;
    
    
    // bounce on borders
    if (p->px > 1 || p->px < 0) {
        p->vx *= -1;
        p->px = roundf(p->px);
    }
    
    if (p->py > 1 || p->py < 0) {
        p->vy *= -1;
        p->py = roundf(p->py);
    }
}

void updateEnnemy(Mob *e, Mob p) {
    if (e->px - p.px < 0.1){
        e->vy += ((p.py - e->py) > 0)? 0.0001 : -0.0001;
        e->vy *= .9;
    } else {
        e->vy = sinf((p.px - e->px)*100)/1000;
    }
    
    e->px += e->vx;
    e->py += e->vy;
}

void updateProjectile(Mob *p) {
    // position
    p->px += p->vx + PROGRESS_RATE;
    p->py += p->vy;
}
