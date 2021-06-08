#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    //prompting the user for height input
    do
    {
        height = get_int("height=");
    }
    while (height < 1 || height > 8);
    
    //drawing the left pyramid
    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= (height - i); j++)
        {
            printf(" ");
        }
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        printf("  ");
        // drawing the right pyramid
        for (int l = 1; l <= i; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}
