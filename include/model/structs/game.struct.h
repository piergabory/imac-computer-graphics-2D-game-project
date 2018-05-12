#ifndef game_struct_h
#define game_struct_h

// main game structure
typedef struct game{
    /**
     *  @ref to the actively played levels
     */
    Level *level;
    
    /**
     * @var Chained list of active enemies
     */
    MobList enemies;
    
    /**
     * @var Chained list of available bonuses
     */
    MobList bonuses;
    
    /**
     * @var Chained list of flying player projectiles
     */
    MobList projectiles;
    
    /**
     * @var Chained list of flying enemy projectiles
     */
    MobList enemy_projectiles;
    
    /**
     * @ref To the player's mobile struct
     */
    Mob *player;
} Game;

#endif /* level_game_h */
