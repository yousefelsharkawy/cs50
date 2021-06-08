#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    int letters = 0, words = 1, sentences = 0, index; 
    float l, s;
    // Prompting the user for input (text)
    string text = get_string("text: ");

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Counting the number of letters
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            letters += 1;
        }
        // Counting the number of words
        else if (text[i] == ' ')
        {
            words += 1;
        }
        // Counting the number of sentences
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences += 1;   
        }
    }
    // Calculating Coleman-Liau index
    l = roundf((letters * 100) / (float)words * 100) / 100;
    s = roundf((sentences * 100) / (float)words * 100) / 100;
    index = roundf(0.0588 * l - 0.296 * s - 15.8);
    // Printing the results
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else 
    {
        printf("Grade %i\n", index);
    }
}
