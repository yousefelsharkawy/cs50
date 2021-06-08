#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Ensuring that there is only one command line argument
    if (argc != 2)
    {
        return 1;
    }
    // Opening the file at the command line line argument in the reading mode
    FILE *memory = fopen(argv[1], "r");
    if (memory == NULL)
    {
        return 1;
    }
    // Creating a temporary storage for each 512 bytes
    BYTE temp[512];
    int i = 0;
    // Allocating space for the file name
    char *filename = malloc(3 * sizeof(char));
    int n = fread(temp, 1, 512, memory);
    while (n == 512)
    {
        if (temp[0] == 0xff && temp[1] == 0xd8 && temp[2] == 0xff && ((temp[3] & 0xf0) == 0xe0))
        {
            sprintf(filename, "%03i.jpg", i);
            FILE *image = fopen(filename, "w");
            do
            {
                fwrite(temp, 1, 512, image);
                n = fread(temp, 1, 512, memory);
                if (n != 512)
                {
                    return 0;
                }
            }
            while (!(temp[0] == 0xff && temp[1] == 0xd8 && temp[2] == 0xff && ((temp[3] & 0xf0) == 0xe0)));
            fclose(image);
            i++;
        }
        else
        {
            n = fread(temp, 1, 512, memory);    
        }
    }
    free(filename);
}
