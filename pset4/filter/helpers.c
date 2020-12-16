#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //set base case of recursion
    if (height == -1)
    {
        return;
    }

    int h = height - 1;

    //loop over all pixels in row
    for (int w = width - 1; w >= 0; w--)
    {
        //get average value of RGBTRIPLE in pixel
        int average = round(((double)image[h][w].rgbtBlue + (double)image[h][w].rgbtGreen + (double)image[h][w].rgbtRed) / 3);

        //convert all values of pixel to average value
        image[h][w].rgbtBlue = image[h][w].rgbtGreen = image[h][w].rgbtRed = (int)average;
    }

    //recurse function on row above
    grayscale(height - 1, width, image);
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    height--;

    //determine midpoint
    int midpoint = (width / 2);

    if (midpoint != 1 && (midpoint & 1) == 0)
        midpoint--;

    // Set variable for accessing correct image array struct
    int h = height;
    int w = width - 1;

    // Set variables for case of 2 pixel width
    if (width == 2)
    {
        w = 1;
        midpoint = 0;
    }

    // swap pixel with equivalent reflected pixel
    for (int i = midpoint; i >= 0; i--)
    {
        RGBTRIPLE tmp = image[h][i];
        image[h][i] = image[h][w - i];
        image[h][w - i] = tmp;
    }

    //set base case of recursion
    if (height < 1)
        return;
    else
        // recurse function on row above
        reflect(height, width, image);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory for image copy array
    RGBTRIPLE(*imagecopy)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // Iterate over image pixels
    for (int i = height - 1; i >= 0; i--)
        for (int j = width - 1; j >= 0; j--)
        {
            // Populate image copy with average values from original, checking for pixel position
            int average[3] = { 0 };
            average[0] = image[i][j].rgbtBlue;
            average[1] = image[i][j].rgbtGreen;
            average[2] = image[i][j].rgbtRed;
            int pixelCount = 1;

            if (i != 0 && j != 0)
            {
                // Case of top-left pixel
                average[0] += image[i - 1][j - 1].rgbtBlue;
                average[1] += image[i - 1][j - 1].rgbtGreen;
                average[2] += image[i - 1][j - 1].rgbtRed;
                pixelCount++;
            }
            if (i != 0)
            {
                // Case of top-middle pixel
                average[0] += image[i - 1][j].rgbtBlue;
                average[1] += image[i - 1][j].rgbtGreen;
                average[2] += image[i - 1][j].rgbtRed;
                pixelCount++;
            }
            if (i != 0 && j != width - 1)
            {
                // Case of top-right pixel
                average[0] += image[i - 1][j + 1].rgbtBlue;
                average[1] += image[i - 1][j + 1].rgbtGreen;
                average[2] += image[i - 1][j + 1].rgbtRed;
                pixelCount++;
            }
            if (j != width - 1)
            {
                // Case of right-middle pixel
                average[0] += image[i][j + 1].rgbtBlue;
                average[1] += image[i][j + 1].rgbtGreen;
                average[2] += image[i][j + 1].rgbtRed;
                pixelCount++;
            }
            if (i != height - 1 && j != width - 1)
            {
                // Case of bottom-right pixel
                average[0] += image[i + 1][j + 1].rgbtBlue;
                average[1] += image[i + 1][j + 1].rgbtGreen;
                average[2] += image[i + 1][j + 1].rgbtRed;
                pixelCount++;
            }
            if (i != height - 1)
            {
                // Case of bottom-middle pixel
                average[0] += image[i + 1][j].rgbtBlue;
                average[1] += image[i + 1][j].rgbtGreen;
                average[2] += image[i + 1][j].rgbtRed;
                pixelCount++;
            }
            if (i != height - 1 && j != 0)
            {
                // Case of bottom-left pixel
                average[0] += image[i + 1][j - 1].rgbtBlue;
                average[1] += image[i + 1][j - 1].rgbtGreen;
                average[2] += image[i + 1][j - 1].rgbtRed;
                pixelCount++;
            }
            if (j != 0)
            {
                // Case of left-middle pixel
                average[0] += image[i][j - 1].rgbtBlue;
                average[1] += image[i][j - 1].rgbtGreen;
                average[2] += image[i][j - 1].rgbtRed;
                pixelCount++;
            }

            //Round, average and cap average array
            for (int k = 0; k < 3; k++)
            {
                average[k] = round((double)average[k] / (double)pixelCount);
                if (average[k] > 255)
                    average[k] = 255;
            }

            // Populate image copy
            imagecopy[i][j].rgbtBlue = average[0];
            imagecopy[i][j].rgbtGreen = average[1];
            imagecopy[i][j].rgbtRed = average[2];
        }

    // Iterate over image and copy image to original
    for (int i = 0; i <= height; i ++)
        for (int j = 0; j <= width; j++)
            image[i][j] = imagecopy[i][j];

    // Free allocated memory
    free(imagecopy);
    return;

}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory for image copy array
    RGBTRIPLE(*imagecopy)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // Iterate over image pixels
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            // Sum variables for Sobel algorithm based of 3x3 grid centred on current pixel
            int gx[3] = { 0 };
            int gy[3] = { 0 };
            int gsobel[3] = { 0 };

            if (i != 0 && j != 0)
            {
                // Case of top-left pixel
                gx[0] -= image[i - 1][j - 1].rgbtBlue;
                gx[1] -= image[i - 1][j - 1].rgbtGreen;
                gx[2] -= image[i - 1][j - 1].rgbtRed;
                gy[0] -= image[i - 1][j - 1].rgbtBlue;
                gy[1] -= image[i - 1][j - 1].rgbtGreen;
                gy[2] -= image[i - 1][j - 1].rgbtRed;
            }
            if (i != 0)
            {
                // Case of top-middle pixel
                gy[0] -= image[i - 1][j].rgbtBlue * 2;
                gy[1] -= image[i - 1][j].rgbtGreen * 2;
                gy[2] -= image[i - 1][j].rgbtRed * 2;
            }
            if (i != 0 && j != width - 1)
            {
                // Case of top-right pixel
                gx[0] += image[i - 1][j + 1].rgbtBlue;
                gx[1] += image[i - 1][j + 1].rgbtGreen;
                gx[2] += image[i - 1][j + 1].rgbtRed;
                gy[0] -= image[i - 1][j + 1].rgbtBlue;
                gy[1] -= image[i - 1][j + 1].rgbtGreen;
                gy[2] -= image[i - 1][j + 1].rgbtRed;
            }
            if (j != width - 1)
            {
                // Case of right-middle pixel
                gx[0] += image[i][j + 1].rgbtBlue * 2;
                gx[1] += image[i][j + 1].rgbtGreen * 2;
                gx[2] += image[i][j + 1].rgbtRed * 2;
            }
            if (i != height - 1 && j != width - 1)
            {
                // Case of bottom-right pixel
                gx[0] += image[i + 1][j + 1].rgbtBlue;
                gx[1] += image[i + 1][j + 1].rgbtGreen;
                gx[2] += image[i + 1][j + 1].rgbtRed;
                gy[0] += image[i + 1][j + 1].rgbtBlue;
                gy[1] += image[i + 1][j + 1].rgbtGreen;
                gy[2] += image[i + 1][j + 1].rgbtRed;
            }
            if (i != height - 1)
            {
                // Case of bottom-middle pixel
                gy[0] += image[i + 1][j].rgbtBlue * 2;
                gy[1] += image[i + 1][j].rgbtGreen * 2;
                gy[2] += image[i + 1][j].rgbtRed * 2;
            }
            if (i != height - 1 && j != 0)
            {
                // Case of bottom-left pixel
                gx[0] -= image[i + 1][j - 1].rgbtBlue;
                gx[1] -= image[i + 1][j - 1].rgbtGreen;
                gx[2] -= image[i + 1][j - 1].rgbtRed;
                gy[0] += image[i + 1][j - 1].rgbtBlue;
                gy[1] += image[i + 1][j - 1].rgbtGreen;
                gy[2] += image[i + 1][j - 1].rgbtRed;
            }
            if (j != 0)
            {
                // Case of left-middle pixel
                gx[0] -= image[i][j - 1].rgbtBlue * 2;
                gx[1] -= image[i][j - 1].rgbtGreen * 2;
                gx[2] -= image[i][j - 1].rgbtRed * 2;
            }

            // Run sobel algorithm on channels, capping at 255 max
            for (int k = 0; k < 3; k++)
            {
                gsobel[k] = round((double)sqrt(((double)gx[k] * (double)gx[k]) + ((double)gy[k] * (double)gy[k])));
                if (gsobel[k] > 255)
                    gsobel[k] = 255;
            }

            // Populate image copy
            imagecopy[i][j].rgbtBlue = gsobel[0];
            imagecopy[i][j].rgbtGreen = gsobel[1];
            imagecopy[i][j].rgbtRed = gsobel[2];

        }

    // Iterate over image and copy image to original
    for (int i = 0; i <= height; i ++)
        for (int j = 0; j <= width; j++)
            image[i][j] = imagecopy[i][j];

    // Free allocated memory
    free(imagecopy);

    return;
}