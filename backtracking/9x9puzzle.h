#ifndef 9X9PUZZLE_H
#define 9X9PUZZLE_H

enum sizes {ROW = 9,
            COL = 9,
            BOX_ACROSS = 3,
            BOX_DOWN = 3,
            ROW_PER_BOX = 3,
            COL_PER_BOX = 3,
            TOTAL_SQUARES = 81,
            MAX_NUM = 9};


int grid9x9_1[ROW][COL] = 
                {{1,0,0,5,0,6,8,0,0},
                 {5,0,0,0,0,0,0,1,0},
                 {0,2,0,4,3,0,9,0,5},
                 {4,5,0,0,0,9,0,8,0},
                 {3,0,1,0,4,0,7,0,6},
                 {0,7,0,1,0,0,0,5,2},
                 {7,0,9,0,6,2,0,4,0},
                 {0,4,0,0,0,0,0,0,1},
                 {0,0,5,8,0,4,0,0,9}};

#endif
