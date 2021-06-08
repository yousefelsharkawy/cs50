#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg = 0;
    // Looping for each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculating the average
            avg = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            avg = round(avg);
            // Setting the new average value to all the pixels
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Looping for each row
    for (int i = 0; i < height; i++)
    {
        // Looping throught the same row twice at the same time, one from the left and one from the right
        int k = width - 1;
        for (int j = 0; j < width; j++)
        {
            if (k >= j)
            {
                if (k >= 0)
                {
                    // Swaping the most right pixel with the most left pixel
                    RGBTRIPLE temp = image[i][j];
                    image[i][j] = image[i][k];
                    image[i][k] = temp;
                    k --;
                }
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Making a copy of the image to work  on it.
    RGBTRIPLE copy[height][width];
    for (int l = 0; l < height; l++)
    {
        for (int m = 0; m < width; m++)
        {
            copy[l][m] = image[l][m];
        }
    }
    // Looping through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Restrict the grid to be one column or one row away (restricting the grid to the neighbour pixels)
            int min_column = j - 1, max_column = j + 1, min_row = i - 1, max_row = i + 1;
            while (min_column < 0)
            {
                min_column++;
            }
            while (max_column > width - 1)
            {
                max_column--;
            }
            while (min_row < 0)
            {
                min_row ++;
            }
            while (max_row > height - 1)
            {
                max_row--;
            }
            // Looping through the smaller grid
            int sum_red = 0, sum_green = 0, sum_blue = 0;
            float n = ((max_column - min_column) + 1) * ((max_row - min_row) + 1);
            for (int I = min_row; I <= max_row; I++)
            {
                for (int J = min_column; J <= max_column; J++)
                {
                    // Calculating the sum of each pixel’s colors
                    sum_red += copy[I][J].rgbtRed;
                    sum_green += copy[I][J].rgbtGreen;
                    sum_blue += copy[I][J].rgbtBlue;
                }
            }
            // Calculating the average of each color
            image[i][j].rgbtRed = round(sum_red / n);
            image[i][j].rgbtGreen = round(sum_green / n);
            image[i][j].rgbtBlue = round(sum_blue / n);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Making a copy of the image to work  on it.
    RGBTRIPLE copy[height][width];
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            copy[k][l] = image[k][l];
        }
    }
    // Looping for each pixel in the 2d array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE box[3][3];
            int m = 0;
            // Looping for the neighbouring pixels to fill up the box of the surrounding pixels 
            for (int I = i - 1; I < i + 2; I++)
            {
                int n = 0;
                for (int J = j - 1; J < j + 2; J++)
                {
                    // If outside the  boundaries, fill as black pixel
                    if (I < 0 || I > (height - 1) || J < 0 || J > (width - 1))
                    {
                        box[m][n].rgbtRed = 0;
                        box[m][n].rgbtGreen = 0;
                        box[m][n].rgbtBlue = 0;
                    }
                    // If inside the boundaries, put it in the box
                    else
                    {
                        box[m][n] = copy[I][J];
                    }
                    n++;
                }
                m++;
            }
            // Creating two of 2d arrays, Gx and Gy
            int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
            int gx_red = 0, gx_green = 0, gx_blue = 0, gy_red = 0, gy_green = 0, gy_blue = 0;
            // Calculating Gx and Gy for each color in the box
            for (int o = 0; o < 3; o++)
            {
                for (int p = 0; p < 3; p++)
                {
                    gx_red += (gx[o][p] * box[o][p].rgbtRed);
                    gx_green += (gx[o][p] * box[o][p].rgbtGreen);
                    gx_blue += (gx[o][p] * box[o][p].rgbtBlue);
                    gy_red += (gy[o][p] * box[o][p].rgbtRed);
                    gy_green += (gy[o][p] * box[o][p].rgbtGreen);
                    gy_blue += (gy[o][p] * box[o][p].rgbtBlue);
                }
            }
            // Taking the square root for Gx^2 + Gy^2 , then rounding to the nearest integer 
            int red = round(sqrt(gx_red * gx_red + (float)gy_red * gy_red));
            int green = round(sqrt((float)gx_green * gx_green + gy_green * gy_green));
            int blue = round(sqrt((float)gx_blue * gx_blue + gy_blue * gy_blue));
            // Ensuring that the square root doesn’t exceed 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            // Setting the new pixel values for each color
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}
