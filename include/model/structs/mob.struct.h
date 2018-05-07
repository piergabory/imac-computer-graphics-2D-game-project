#ifndef mob_struct_h
#define mob_struct_h

//// Mob types definitions.
#define ENEMY 'e'
#define BONUS 'b'
#define OBSTACLE 'o'
#define PLAYER 'p'
#define PROJECTILE 'j'
#define ENNEMY_PROJECTILE 't'

// mob structure define any moving entity (player, enemy, projectiles etc..)
typedef struct mobile {
    /**
     * Velocity vector
     * @var float vx, X coord of velocity vector
     * @var float vy, Y coord of velocity vector
     */
    float vy, vx;
    
    /**
     * Mob position relative to the world dimentions
     * values are between 0 and 1.
     * @var float px, X coord
     * @var float py, Y coord
     */
    float py, px;
    
    /**
     * @var int health of the mob
     */
    int health;
    
    /**
     * @var char type of the mob (defined above)
     */
    unsigned char type;
    
    //// @ref to the next mob chain link
    struct mobile *next;
} Mob, *MobList;


#endif /* mob_struct_h */
