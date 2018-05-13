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
