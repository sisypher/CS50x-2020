#include "helpers.h"
#include <math.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
    
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int GxRed = 0;
            int GxGreen = 0;
            int GxBlue = 0;
            int GyRed = 0;
            int GyGreen = 0;
            int GyBlue = 0;
            
            for (int k = 0; k < 3; k++)
            {
                for (int s = 0; s < 3; s++)
                {
                    
                    // checking that it's not negative and within the height and width ranges
                    if (((j - 1 + s < 0) || (j - 1 + s > width - 1)) || ((i - 1 + k < 0) || (i - 1 + k > height - 1)))
                    {
                        continue;
                    }
                    
                    // Calculating Gx for the channels
                    GxRed += Gx[k][s] * imageCpy[i - 1 + k][j - 1 + s].rgbtRed;
                    GxGreen += Gx[k][s] * imageCpy[i - 1 + k][j - 1 + s].rgbtGreen;
                    GxBlue += Gx[k][s] * imageCpy[i - 1 + k][j - 1 + s].rgbtBlue;
                    
                    // Calculating Gy for the channels
                    GyRed += Gy[k][s] * imageCpy[i - 1 + k][j - 1 + s].rgbtRed;
                    GyGreen += Gy[k][s] * imageCpy[i - 1 + k][j - 1 + s].rgbtGreen;
                    GyBlue += Gy[k][s] * imageCpy[i - 1 + k][j - 1 + s].rgbtBlue;
                }
            }
            
            // Calculating overall G and capping at 255
            int GRed = round(sqrt(GxRed * GxRed + GyRed * GyRed));
            int GGreen = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
            int GBlue = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
            
            if (GRed > 255)
            {
                GRed = 255;
            }
            
            if (GGreen > 255)
            {
                GGreen = 255;
            }
            
            if (GBlue > 255)
            {
                GBlue = 255;
            }
            
            image[i][j].rgbtRed = GRed;
            image[i][j].rgbtGreen = GGreen;
            image[i][j].rgbtBlue = GBlue;
        }
    }
    return;
}
