#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include "grid.h"
#include "backtracking_solver.h"
#include "display_grid.h"
#include "4x4puzzle.h"
#include "9x9puzzle.h"


bool is_number(char input[]);


int main(int argc, char *argv[])
{
    Grid *puzzle;

    int BIG_GRID = 9;
    int SMALL_GRID = 4;

    int grid_size = BIG_GRID;

    if (argc > 1)
    {
            if (is_number(argv[1]))
            {
                    int n = atoi(argv[1]);
                    if (n == SMALL_GRID)
                    {
                            grid_size = n;
                    }
            }
    }

    if (grid_size == SMALL_GRID)
    {
            puzzle = make_grid(grid_size, grid4x4_1);
    }
    else
    {
            puzzle = make_grid(grid_size, grid9x9_1);
    }

    printf("\nPUZZLE\n");
    print_puzzle(puzzle);
    solve_puzzle(puzzle);
    printf("\nSOLUTION\n");
    print_puzzle(puzzle);
    delete_puzzle(puzzle);
}


void delete_puzzle(Grid *puzzle)
{
    for (int row = 0; row < puzzle->ROW; row++)
    {
        for (int col = 0; col < puzzle->COL; col++)
        {
            free(puzzle->squares[row * puzzle->ROW + col]);
        }
    }
    free(puzzle->squares);
    free(puzzle);
}


void solve_puzzle(Grid *puzzle)
{
    int row = 0;
    int col = 0;
    bool moving_forward = true;

    int current_square_num = (row * puzzle->ROW) + col;

    while (current_square_num < puzzle->TOTAL_SQUARES)
    {
        Square *current_square = puzzle->squares[current_square_num];
        
        if (current_square->part_of_puzzle)
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

        if (col >= puzzle->COL)
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
                col = puzzle->COL - 1;
            }
        }
        current_square_num = (row * puzzle->ROW) + col;
    }
}


bool fill_square(Grid *puzzle, int row, int col)
{
    int curr_num = puzzle->squares[row * puzzle->ROW + col]->num;
    int first_try = curr_num;
    
    if (curr_num == 0)
    {
        first_try = 1;
    }
    
    for (int num = first_try; num <= puzzle->MAX_NUM; num++)
    {
        if (num_allowed(puzzle, row, col, num))
        {
            puzzle->squares[row * puzzle->ROW + col]->num = num;
            return true;
        }
    }
    puzzle->squares[row * puzzle->ROW + col]->num = 0;
    return false;
}


Grid *make_grid(int grid_size, int grid[grid_size][grid_size])
{
        Grid *puzzle = malloc(sizeof(*puzzle));
        
        if (puzzle == NULL)
        {
            fprintf(stderr, "Failed to allocate memory for puzzle\n");
            exit(EXIT_FAILURE);
        }

        puzzle->squares = malloc(sizeof(*puzzle->squares) * grid_size * grid_size);

        if (puzzle->squares == NULL)
        {
            fprintf(stderr, "Failed to allocate memory for squares\n");
            exit(EXIT_FAILURE);
        }

        puzzle->ROW = grid_size;
        puzzle->COL = grid_size;
        puzzle->BOX_ACROSS = sqrt(grid_size);
        puzzle->BOX_DOWN = sqrt(grid_size);
        puzzle->ROW_PER_BOX = sqrt(grid_size);
        puzzle->COL_PER_BOX = sqrt(grid_size);
        puzzle->TOTAL_SQUARES = pow(grid_size, 2);
        puzzle->MAX_NUM = grid_size;

        for (int row = 0; row < puzzle->ROW; row++)
        {
                for (int col = 0; col < puzzle->COL; col++)
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

                        puzzle->squares[row * puzzle->ROW + col] = square;
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
    int m_row = min_row(puzzle, row);
    int m_col = min_col(puzzle, col);

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
    for (int col = 0; col < puzzle->COL; col++)
    {
        if (puzzle->squares[row * puzzle->ROW + col]->num == find)
        {
            return true;
        }
    }
    
    return false;
}


bool col_contains(Grid *puzzle, int col, int find)
{
    for (int row = 0; row < puzzle->ROW; row++)
    {
        if (puzzle->squares[row * puzzle->ROW + col]->num == find)
        {
            return true;
        }
    }
    
    return false;
}


bool box_contains(Grid *puzzle, int min_row, int min_col, int find)
{
    int max_row = min_row + (puzzle->ROW / puzzle->BOX_DOWN);
    int max_col = min_col + (puzzle->COL / puzzle->BOX_ACROSS);
    
    for (int row = min_row; row < max_row; row++)
    {
        for (int col = min_col; col < max_col; col++)
        {
            if (puzzle->squares[row * puzzle->ROW + col]->num == find)
            {
                return true;
            }
        }
    }
    
    return false;
}


int min_col(Grid *puzzle, int col)
{
    int min_col = 0;

    if (col >= 2 * puzzle->COL_PER_BOX)
    {
        min_col = 2 * puzzle->COL_PER_BOX;
    }
    else if (col >= puzzle->COL_PER_BOX)
    {
        min_col = puzzle->COL_PER_BOX;
    }
    
    return min_col;
}


int min_row(Grid *puzzle, int row)
{
    int min_row = 0;

    if (row >= 2 * puzzle->ROW_PER_BOX)
    {
        min_row = 2 * puzzle->ROW_PER_BOX;
    }
    else if (row >= puzzle->ROW_PER_BOX)
    {
        min_row = puzzle->ROW_PER_BOX;
    }
    
    return min_row;
}


bool is_number(char input[])
{
        int i = 0;
        if (input[0] == '-') {
                i = 1;
        }
        for (i = i; input[i] != 0; i++)
        {
                if(!isdigit(input[i]))
                {
                        return false;
                }
        }
        return true;
}
