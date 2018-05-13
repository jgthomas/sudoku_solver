#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "display_grid.h"
//#include "4x4puzzle.h"
//#include "6x6puzzle.h"
#include "9x9puzzle.h"


typedef struct Square {
        int num;
        bool part_of_puzzle;
}
Square;


typedef struct Grid {
        Square *squares[ROW][COL];
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


bool row_contains(Grid *puzzle, int row, int find);
bool col_contains(Grid *puzzle, int col, int find);
bool box_contains(Grid *puzzle, int min_row, int min_col, int find);
bool num_allowed(Grid *puzzle, int row, int col, int num);
int min_col(int col);
int min_row(int row);
Square *make_square(int num, bool part_of_puzzle);
//Grid *make_grid(int grid[ROW][COL]);
Grid *make_grid(int grid_size, int grid[ROW][COL]);
void print_puzzle(Grid *puzzle);
bool fill_square(Grid *puzzle, int row, int col);
void solve_puzzle(Grid *puzzle);
void delete_puzzle(Grid *puzzle);


int main()
{
    int grid_size = 9;

    Grid *puzzle = make_grid(grid_size, grid9x9_1);
    print_puzzle(puzzle);
    solve_puzzle(puzzle);
    print_puzzle(puzzle);
    delete_puzzle(puzzle);
}


void delete_puzzle(Grid *puzzle)
{
    for (int row = 0; row < ROW; row++)
    {
        for (int col = 0; col < COL; col++)
        {
            free(puzzle->squares[row][col]);
        }
    }
    free(puzzle);
}


void solve_puzzle(Grid *puzzle)
{
    int row = 0;
    int col = 0;
    int square = (row * ROW) + col;
    Square *square_ptr = NULL;
    bool moving_forward = true;
    
    while (square < TOTAL_SQUARES)
    {
        square_ptr = puzzle->squares[row][col];
        
        if (square_ptr->part_of_puzzle)
        {
            if (moving_forward)
            {
                col++;
            }
            else
            {
                col--;
            }
        }
        else if (fill_square(puzzle, row, col))
        {
            col++;
            moving_forward = true;
        }
        else
        {
            col--;
            moving_forward = false;
        }

        if (col >= COL)
        {
            row++;
            col = 0;
        }
        else if (col < 0)
        {
            if (row == 0)
            {
                printf("Cannot solve puzzle!\n");
                exit(EXIT_FAILURE);
            }
            else
            {
                row--;
                col = COL-1;
            }
        }
        square = (row * ROW) + col;
    }
}


bool fill_square(Grid *puzzle, int row, int col)
{
    int curr_num = puzzle->squares[row][col]->num;
    int first_try = curr_num;
    
    if (curr_num == 0)
    {
        first_try = 1;
    }
    
    for (int num = first_try; num <= MAX_NUM; num++)
    {
        if (num_allowed(puzzle, row, col, num))
        {
            puzzle->squares[row][col]->num = num;
            return true;
        }
    }
    puzzle->squares[row][col]->num = 0;
    return false;
}


Grid *make_grid(int grid_size, int grid[ROW][COL])
{
        Grid *puzzle = malloc(sizeof(*puzzle));
        
        if (puzzle == NULL)
        {
            fprintf(stderr, "Failed to allocate memory for puzzle\n");
            exit(EXIT_FAILURE);
        }

        puzzle->ROW = grid_size;
        puzzle->COL = grid_size;
        puzzle->BOX_ACROSS = sqrt(grid_size);

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
        
        if (square == NULL)
        {
            fprintf(stderr, "Failed to allocate memory for square\n");
            exit(EXIT_FAILURE);
        }
        
        square->num = num;
        square->part_of_puzzle = part_of_puzzle;
        return square;
}


bool num_allowed(Grid *puzzle, int row, int col, int num)
{
    int m_row = min_row(row);
    int m_col = min_col(col);

    if (!row_contains(puzzle, row, num) &&
        !col_contains(puzzle, col, num) &&
        !box_contains(puzzle, m_row, m_col, num))
    {
        return true;
    }
    
    return false;
}


bool row_contains(Grid *puzzle, int row, int find)
{
    for (int col = 0; col < COL; col++)
    {
        if (puzzle->squares[row][col]->num == find)
        {
            return true;
        }
    }
    
    return false;
}


bool col_contains(Grid *puzzle, int col, int find)
{
    for (int row = 0; row < ROW; row++)
    {
        if (puzzle->squares[row][col]->num == find)
        {
            return true;
        }
    }
    
    return false;
}


bool box_contains(Grid *puzzle, int min_row, int min_col, int find)
{
    int max_row = min_row + (ROW / BOX_DOWN);
    int max_col = min_col + (COL / BOX_ACROSS);
    
    for (int row = min_row; row < max_row; row++)
    {
        for (int col = min_col; col < max_col; col++)
        {
            if (puzzle->squares[row][col]->num == find)
            {
                return true;
            }
        }
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


void print_puzzle(Grid *puzzle)
{
        print_divider(ROW);

        for (int row = 0; row < ROW; row++)
        {
                printf("|");

                for (int col = 0; col < COL; col++)
                {
                        int num = puzzle->squares[row][col]->num;
                        
                        if (num == 0)
                        {
                                printf(" - ");
                        }
                        else
                        {
                                printf(" %d ", num);
                        }

                        if ((col+1) % COL_PER_BOX == 0)
                        {
                            printf("|");
                        }
                }

                if ((row+1) % ROW_PER_BOX == 0)
                {
                    print_divider(ROW);
                }
                else
                {
                    printf("\n");
                }
        }
        printf("\n");
}
