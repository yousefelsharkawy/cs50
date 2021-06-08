#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    int k, p, c, P, C;
    // Prompting for suitable command-line argument
    if (argc != 2)
    {
        printf("usage: ./caesar key\n");
        return 1;
    }
    else
    {
        for (int i = 0; argv[1][i] != '\0'; i++)
        {
            if (argv[1][i] >= '0' && argv[1][i] <= '9')
            {
            }
            else
            {
                printf("usage: ./caesar key\n");
                return 1;
            }
        }
    }
    // Converting the string characters into an integer
    k = atoi(argv[1]);
    // Prompting the user for plaintext input
    string plain = get_string("plaintext:  ");
    // Converting the plain text to ciphertext
    for (int j = 0, n = strlen(plain); j < n; j++)
    {
        if (plain[j] >= 'a' && plain[j] <= 'z')
        {
            // p is the i^th place of the character in the plaintext
            // c is the i^th place of the character in the ciphertext
            p = plain[j] - 97;
            c = (p + k) % 26;
            plain[j] = c + 97;
        }
        else if (plain[j] >= 'A' && plain[j] <= 'Z')
        {
            // P is the i^th place of the capital character in the plaintext
            // C is the i^th place of the capital character in the ciphertext
            P = plain[j] - 65;
            C = (P + k) % 26;
            plain[j] = C + 65;
        }
    }
    // Printing the ciphertext
    printf("ciphertext: %s\n", plain);
    return 0;
}