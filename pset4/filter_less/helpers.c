#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer;
    //Set the for loop for every pixel
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            //Calculate the average value of RGB and set the grayscale accordingly
            buffer = image[y][x];
            int avg = round((buffer.rgbtBlue + buffer.rgbtGreen + buffer.rgbtRed) / 3.00);
            buffer.rgbtBlue = avg;
            buffer.rgbtGreen = avg;
            buffer.rgbtRed = avg;
            image[y][x] = buffer;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer;
    //Set the for loop for every pixel
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            buffer = image[y][x];
            //Calculate the seppia value
            int tmp = 0;
            tmp = round(0.272 * image[y][x].rgbtRed + 0.534 * image[y][x].rgbtGreen + 0.131 * image[y][x].rgbtBlue);
            //Check if the value is over the maximum of 255 and do the substitution
            if (tmp > 255)
            {
                buffer.rgbtBlue = 255;
            }
            else
            {
                buffer.rgbtBlue = tmp;
            }

            //Calculate the seppia value
            tmp = round(0.349 * image[y][x].rgbtRed + 0.686 * image[y][x].rgbtGreen + 0.168 * image[y][x].rgbtBlue);
            //Check if the value is over the maximum of 255 and do the substitution
            if (tmp > 255)
            {
                buffer.rgbtGreen = 255;
            }
            else
            {
                buffer.rgbtGreen = tmp;
            }

            //Calculate the seppia value
            tmp = round(0.393 * image[y][x].rgbtRed + 0.769 * image[y][x].rgbtGreen + 0.189 * image[y][x].rgbtBlue);
            //Check if the value is over the maximum of 255 and do the substitution
            if (tmp > 255)
            {
                buffer.rgbtRed = 255;
            }
            else
            {
                buffer.rgbtRed = tmp;
            }

            image[y][x] = buffer;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Set the for loop for every pixel
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width / 2; x++)
        {
            RGBTRIPLE buffer;
            buffer = image[y][x];
            image[y][x] = image[y][width - 1 - x];
            image[y][width - 1 - x] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Create a copy of the whole image for pixel reference
    RGBTRIPLE image_reference[height][width];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            image_reference[y][x] = image[y][x];
        }
    }
    //Apply the filter
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            //Calucale the blurred pixel value
            int red_sum = 0;
            int blue_sum = 0;
            int green_sum = 0;
            float addendum_counter = 0;
            for (int yc = - 1; yc <= 1; yc++)
            {
                for (int xc = - 1; xc <= 1; xc++)
                {
                    if ((yc + y) >= 0 && (yc + y) < (height) && (xc + x) >= 0 && (xc + x) < (width))
                    {
                        red_sum += image_reference[yc + y][xc + x].rgbtRed;
                        blue_sum += image_reference[yc + y][xc + x].rgbtBlue;
                        green_sum += image_reference[yc + y][xc + x].rgbtGreen;
                        addendum_counter++;
                    }
                }
            }
            image[y][x].rgbtRed = round(red_sum / addendum_counter);
            image[y][x].rgbtGreen = round(green_sum / addendum_counter);
            image[y][x].rgbtBlue = round(blue_sum / addendum_counter);
        }
    }
    return;
}
