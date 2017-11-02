#ifndef 6X6PUZZLE_H
#define 6X6PUZZLE_H

enum sizes {ROW = 6,
            COL = 6,
            BOX_ACROSS = 2,
            BOX_DOWN = 3,
            ROW_PER_BOX = 2,
            COL_PER_BOX = 3,
            TOTAL_SQUARES = 36,
            MAX_NUM = 6};


int grid6x6_1[ROW][COL] = {{1,0,0,0,4,0},
                           {0,0,4,6,0,0},
                           {2,0,0,0,3,6},
                           {6,1,0,0,0,2},
                           {0,0,1,3,0,0},
                           {0,3,0,0,0,5}};

#endif
