#ifndef level_struct_h
#define level_struct_h

// statuses
#define STATUS_PLAYING 0
#define STATUS_LEVEL_COMPLETE 1
#define STATUS_GAME_OVER -1

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
    int status;
    
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
