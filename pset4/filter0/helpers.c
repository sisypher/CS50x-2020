#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (image[i][j].rgbtBlue == image[i][j].rgbtGreen && image[i][j].rgbtBlue == image[i][j].rgbtRed)
            {
                continue; // skips any following code and contiues to the next iteration
            }

            int avgColor = round(((float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3));

            image[i][j].rgbtBlue = avgColor;
            image[i][j].rgbtGreen = avgColor;
            image[i][j].rgbtRed = avgColor;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * (float)image[i][j].rgbtRed + .769 * (float)image[i][j].rgbtGreen + .189 * (float)image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * (float)image[i][j].rgbtRed + .686 * (float)image[i][j].rgbtGreen + .168 * 
                                   (float)image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * (float)image[i][j].rgbtRed + .534 * (float)image[i][j].rgbtGreen + .131 * (float)image[i][j].rgbtBlue);
            
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// function to swap pixels
void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE temp = *a;
    *a = *b;
    *b = temp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][width - 1 - j]);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCpy[height][width];
    
    // loop to make a copy of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCpy[i][j].rgbtRed = image[i][j].rgbtRed;
            imageCpy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imageCpy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            
            // extracting a 3x3 grid to calculate the average of R & G & B for every pixel
            
            int redSum = 0;
            int greenSum = 0;
            int blueSum = 0;
            int pixelCount = 0;
            
            for (int k = i - 1; k <= i + 1; k++)
            {
                
                // checking that it's not negative and within the height range
                if ((k < 0) || (k > height - 1))
                {
                    continue;
                }
                
                for (int s = j - 1; s <= j + 1; s++)
                {
                    
                    // checking that it's not negative and within the height range
                    if ((s < 0) || (s > width - 1))
                    {
                        continue;
                    }
                    
                    redSum += imageCpy[k][s].rgbtRed;
                    greenSum += imageCpy[k][s].rgbtGreen;
                    blueSum += imageCpy[k][s].rgbtBlue;
                    pixelCount++;
                }
            }
            
            // calculating the average for R & G & B
            int avgRed = round((float)(redSum) / pixelCount);
            int avgGreen = round((float)(greenSum) / pixelCount);
            int avgBlue = round((float)(blueSum) / pixelCount);
            
            // assigning the average value for R & G & B to the pixel
            image[i][j].rgbtRed = avgRed;
            image[i][j].rgbtGreen = avgGreen;
            image[i][j].rgbtBlue = avgBlue;
        }
    }
    return;
}
