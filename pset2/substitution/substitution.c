#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[])
{
    int p;
    // Prompting the user for a command-line argument
    if (argc != 2)
    {
        printf("usage: ./substitution key\n");
        return 1;
    }
    else
    {
        int n = strlen(argv[1]);
        // Prompting the user for the command-line argument to be 26 digits 
        if (n != 26)
        {
            printf("key must contain 26 characters\n");
            return 1;
        }
        else
        {
            // Prompting the user for the 26 digits to be alphabetic characters
            for (int i = 0; i < n; i++)
            {
                if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
                {
                }
                else if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
                {
                }
                else
                {
                    printf("usage: ./substitution key\n");
                    return 1;
                }
            }
            for (int i = 0; i < n; i++)
            {
                if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
                {
                    argv[1][i] += 32; 
                }
            }
            // Prompting the user for non-repeated characters in key
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    if (j != k)
                    {
                        if (argv[1][j] == argv[1][k])
                        {
                            printf("key must contain unrepeated characters.\n");
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // Prompting the user for a plaintext argument
    string text = get_string("plaintext:  ");
    for (int l = 0, N = strlen(text); l < N; l++)
    {
        // Crypting the lowercase plaintext characters to ciphertext
        if (text[l] >= 'a' && text[l] <= 'z')
        {
            // p is the position of the i^th lowercase character in the plaintext
            p = text[l] - 97;
            // substitue the corresponding character in key with character in plaintext
            text[l] = argv[1][p];
        }
        // Crypting the uppercase plaintext characters to ciphertext 
        else if (text[l] >= 'A' && text[l] <= 'Z')
        {
            // p is the position of the i^th uppercase character in the plaintext
            p = text[l] - 65;
            // Change the corresponding character in key to uppercase then substitute 
            text[l] = argv[1][p] - 32;
        }
    }
    // Printing the ciphertext
    printf("ciphertext: %s\n", text);
    return 0;
}