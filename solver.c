#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


enum sizes {ROW = 4,
            COL = 4,
            BOX_ACROSS = 2,
            BOX_DOWN = 2,
            ROW_PER_BOX = 2,
            COL_PER_BOX = 2,
            TOTAL_SQUARES = 16};


typedef struct Square {
        int num;
        bool part_of_puzzle;
}
Square;


typedef struct Grid {
        Square *squares[ROW][COL];
}
Grid;


bool box_contains(int grid[ROW][COL], int min_row, int min_col, int find);
bool row_contains(int grid[ROW][COL], int row, int find);
bool col_contains(int grid[ROW][COL], int col, int find);
int min_col(int col);
int min_row(int row);
bool num_allowed(int grid[ROW][COL], int row, int col, int num);
Square *make_square(int num, bool part_of_puzzle);
Grid *make_grid(int grid[ROW][COL]);
void print_puzzle(Grid *puzzle);


int main()
{
    /*int grid[ROW][COL] = {{0,0,3,6,0,0},
                          {0,2,0,0,4,0},
                          {5,0,0,0,6,0},
                          {0,3,0,0,0,5},
                          {3,0,0,0,1,0},
                          {0,0,1,4,0,0}};*/
    

    int grid[ROW][COL] = {{0,0,4,2},
                          {4,0,3,0},
                          {0,4,0,3},
                          {0,1,0,0}};


    Grid *puzzle = make_grid(grid);
    print_puzzle(puzzle);

    int num = 4;
    
    for (int row = 0; row < ROW; row++)
    {
        for (int col = 0; col < COL; col++)
        {
            if (num_allowed(grid, row, col, num))
            {
                grid[row][col] = num;
            }
        }
    }
}


Grid *make_grid(int grid[ROW][COL])
{
        Grid *puzzle = malloc(sizeof(*puzzle));

        for (int row = 0; row < ROW; row++)
        {
                for (int col = 0; col < COL; col++)
                {
                        int num = grid[row][col];
                        Square *square;

                        if (num == 0)
                        {
                                square = make_square(num, false);
                        }
                        else
                        {
                                square = make_square(num, true);
                        }

                        puzzle->squares[row][col] = square;
                }
        }

        return puzzle;
}


Square *make_square(int num, bool part_of_puzzle)
{
        Square *square = malloc(sizeof(*square));
        square->num = num;
        square->part_of_puzzle = part_of_puzzle;
        return square;
}


bool num_allowed(int grid[ROW][COL], int row, int col, int num)
{
    int m_row = min_row(row);
    int m_col = min_col(col);

    if (!row_contains(grid, row, num) &&
        !col_contains(grid, col, num) &&
        !box_contains(grid, m_row, m_col, num))
    {
        return true;
    }
    
    return false;
}


int min_col(int col)
{
    int min_col = 0;
    
    if (col >= 2 * COL_PER_BOX)
    {
        min_col = 2 * COL_PER_BOX;
    }
    else if (col >= COL_PER_BOX)
    {
        min_col = COL_PER_BOX;
    }
    
    return min_col;
}


int min_row(int row)
{
    int min_row = 0;
    
    if (row >= 2 * ROW_PER_BOX)
    {
        min_row = 2 * ROW_PER_BOX;
    }
    else if (row >= ROW_PER_BOX)
    {
        min_row = ROW_PER_BOX;
    }
    
    return min_row;
}


bool box_contains(int grid[ROW][COL], int min_row, int min_col, int find)
{
    int max_row = min_row + ROW / BOX_DOWN;
    int max_col = min_col + COL / BOX_ACROSS;
    
    for (int row = min_row; row < max_row; row++)
    {
        for (int col = min_col; col < max_col; col++)
        {
            if (grid[row][col] == find)
            {
                return true;
            }
        }
    }
    
    return false;
}


bool row_contains(int grid[ROW][COL], int row, int find)
{
    for (int col = 0; col < COL; col++)
    {
        if (grid[row][col] == find)
        {
            return true;
        }
    }
    
    return false;
}


bool col_contains(int grid[ROW][COL], int col, int find)
{
    for (int row = 0; row < ROW; row++)
    {
        if (grid[row][col] == find)
        {
            return true;
        }
    }
    
    return false;
}


void print_puzzle(Grid *puzzle)
{
        for (int row = 0; row < ROW; row++)
        {
                for (int col = 0; col < COL; col++)
                {
                        int num = puzzle->squares[row][col]->num;

                        if (num == 0)
                        {
                                printf("_  ");
                        }
                        else
                        {
                                printf("%d  ", num);
                        }
                }
                printf("\n");
        }
        printf("\n");
}
