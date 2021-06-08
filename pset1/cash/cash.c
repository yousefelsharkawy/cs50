#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollars;
    int cents, i = 0;
    do
    {
        dollars = get_float("change owed:");
        cents = round(dollars * 100);
    }
    while (dollars < 0);
    
    if (cents >= 25)
    {
        i = cents / 25;
        cents = cents % 25;
    }
    if (cents >= 10)
    {
        i = i + (cents / 10);
        cents = cents % 10;
    }
    if (cents >= 5)
    {
        i = i + (cents / 5);
        cents = cents % 5;
    }
    if (cents >= 1)
    {
        i = i + (cents / 1);
        cents = cents % i;
    }
    if (cents == 0)
    {
        i = i + 0;
    }
    printf("%i\n", i);
    
}