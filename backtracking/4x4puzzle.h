#ifndef 4X4PUZZLE_H
#define 4X4PUZZLE_H

enum sizes {ROW = 4,
            COL = 4,
            BOX_ACROSS = 2,
            BOX_DOWN = 2,
            ROW_PER_BOX = 2,
            COL_PER_BOX = 2,
            TOTAL_SQUARES = 16,
            MAX_NUM = 4};


int grid4x4_1[ROW][COL] = {{0,0,4,2},
                           {4,0,3,0},
                           {0,4,0,3},
                           {0,1,0,0}};


int grid4x4_2[ROW][COL] = {{0,2,0,1},
                           {1,0,0,0},
                           {0,0,0,4},
                           {4,0,3,0}};

#endif
