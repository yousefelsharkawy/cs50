#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int j, k = 0, l = 0 ;
    long n = get_long("number=");
    long m = n;
    for (int i = 1; n != 0; i++)
    {
        // j is the digit extracted from the number starting from right to the left 
        j = n % 10;
        n = (n - (n % 10)) / 10;
        if (i % 2 != 0)
        {
            // k is the sum of the odd digits of the entered number starting from the most right digit
            k = k + j;  
        }
        else 
        {
            // l is the sum of the even digits of the entered number starting from the next to most right digit (after multiplied by 2)
            if (2 * j < 9)
            {
                l = l + 2 * j; 
            }
            else 
            {
                l = l + ((2 * j / 10) + (2 * j % 10));
            }
        }
    }
    if (((l + k) % 10) != 0)
    {
        printf("INVALID\n");
    }
    else 
    {
        if (((m / 1000000000000) == 4) || ((m / 1000000000000000) == 4))
        {
            printf("VISA\n");
        }
        else if ((m / 10000000000000) == 34 || (m / 10000000000000) == 37)
        {
            printf("AMEX\n");
        }
        else if ((m / 100000000000000) == 51 || (m / 100000000000000) == 52 || (m / 100000000000000) == 53 || (m / 100000000000000) == 54
                 || (m / 100000000000000) == 55)
        {
            printf("MASTERCARD\n");
        }
        else 
        {
            printf("INVALID\n");
        }
        
    }
}