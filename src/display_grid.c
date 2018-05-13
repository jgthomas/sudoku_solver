#include <stdio.h>
#include "display_grid.h"
#include "grid.h"


void print_divider(int len)
{
    printf("\n");
    for (int i = 0; i < len; i++)
    {
        printf("---");
    }
    printf("----\n");
}


void print_puzzle(Grid *puzzle)
{
        print_divider(puzzle->ROW);

        for (int row = 0; row < puzzle->ROW; row++)
        {
                printf("|");

                for (int col = 0; col < puzzle->COL; col++)
                {
                        int num = puzzle->squares[row * puzzle->ROW + col]->num;
                        
                        if (num == 0)
                        {
                                printf(" - ");
                        }
                        else
                        {
                                printf(" %d ", num);
                        }

                        if ((col+1) % puzzle->COL_PER_BOX == 0)
                        {
                            printf("|");
                        }
                }

                if ((row+1) % puzzle->ROW_PER_BOX == 0)
                {
                    print_divider(puzzle->ROW);
                }
                else
                {
                    printf("\n");
                }
        }
        printf("\n");
}
