#ifndef level_struct_h
#define level_struct_h

// statuses
typedef enum {
    PLAYING,
    LEVEL_COMPLETE,
    GAME_OVER
} GameStatus;

typedef enum {
    VOID,
    OBSTACLE,
    FINISH_LINE = 18
} TerrainType;

// level structure collecting world obstacles and game progress
typedef struct level {
    /**
     * @var float progress, between 0 and 1,
     * -> progress of the player through the level
     */
    float progress;
    
    /**
     * @var int status,
     * -> 0 if the game is running
     * -> positive if player has reached the end of level safely
     * -> negative if the player died
     */
    GameStatus status;
    
    /**
     * Level dimentions in 'blocks'
     * @var unsigned int width,
     * @var unsigned int height,
     */
    unsigned int width, height;
    
    /**
     * @var unsigned int 2d arrays
     * -> values are 0 for air blocks or any other value for terrain blocs
     */
    unsigned int **map;
} Level;


#endif /* level_struct_h */
