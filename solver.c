#include <stdio.h>
#include <stdbool.h>


enum sizes {ROW = 4, COL = 4, BOX_ACROSS = 2, BOX_DOWN = 2, ROW_PER_BOX = 2, COL_PER_BOX = 2};


void print_grid(int grid[ROW][COL]);
bool box_contains(int grid[ROW][COL], int min_row, int min_col, int find);
bool row_contains(int grid[ROW][COL], int row, int find);
bool col_contains(int grid[ROW][COL], int col, int find);
int min_col(int col);
int min_row(int row);
bool num_allowed(int grid[ROW][COL], int row, int col, int num);


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

    int num = 4;
    
    print_grid(grid);
    
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

    print_grid(grid);
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


void print_grid(int grid[ROW][COL])
{
    for (int row = 0; row < ROW; row++) 
    {
        for (int col = 0; col < COL; col++) 
        {
            if (grid[row][col] == 0)
            {
                printf("_  ");
            }
            else
            {
                printf("%d  ", grid[row][col]);
            }
        }
        printf("\n");
    }
    printf("\n");
}
