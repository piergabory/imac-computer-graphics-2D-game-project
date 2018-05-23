#ifndef mob_struct_h
#define mob_struct_h

#define BONUS_TYPE_COUNT 3

//// Mob types definition
typedef enum {
    ENEMY,
    BONUS_HEALTH,
    BONUS_WEAPON,
    BONUS_SPEED,
    PLAYER,
    PROJECTILE,
    ENEMY_PROJECTILE
} MobType;

// mob structure define any moving entity (player, enemy, projectiles etc..)
typedef struct _mobile {
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
     * @var int projectile_clock
     */
    unsigned int projectile_clock;
    
    /**
     * @var int reload_time
     */
    unsigned int reload_time;
    
    /**
     * @var int bullet_count
     */
    unsigned int bullet_count;
    
    /**
     * @var float max_speed
     */
    float max_speed;
    
    /**
     * @var char type of the mob (defined above)
     */
    MobType type;
    
    //// @ref to the next mob chain link
    struct _mobile *next;
} Mob, *MobList;


#endif /* mob_struct_h */
