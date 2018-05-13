#ifndef GRID_H
#define GRID_H

typedef struct Square {
        int num;
        bool part_of_puzzle;
}
Square;


typedef struct Grid {
        Square **squares;
        int ROW;
        int COL;
        int BOX_ACROSS;
        int BOX_DOWN;
        int ROW_PER_BOX;
        int COL_PER_BOX;
        int TOTAL_SQUARES;
        int MAX_NUM;
}
Grid;

#endif
