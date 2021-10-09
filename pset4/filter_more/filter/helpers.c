#include "helpers.h"
#include <math.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
    //Set the loop for every pixel
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            //Declare the gx and gy support variables
            int gy_red = 0;
            int gy_blue = 0;
            int gy_green = 0;
            int gx_red = 0;
            int gx_blue = 0;
            int gx_green = 0;

            //Calucale the Gx pixel value
            for (int yc = - 1; yc <= 1; yc++)
            {
                for (int xc = - 1; xc <= 1; xc++)
                {
                    //Set the Gx matrix and the temporary colors variables
                    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
                    //Calculate the Gx value for each pixel
                    if ((yc + y) >= 0 && (yc + y) < (height) && (xc + x) >= 0 && (xc + x) < (width))
                    {
                        gx_red += (image_reference[yc + y][xc + x].rgbtRed) * gx[yc + 1][xc + 1];
                        gx_blue += (image_reference[yc + y][xc + x].rgbtBlue) * gx[yc + 1][xc + 1];
                        gx_green += (image_reference[yc + y][xc + x].rgbtGreen) * gx[yc + 1][xc + 1];
                    }
                }
            }
            //Calucale the Gy pixel value
            for (int yc = - 1; yc <= 1; yc++)
            {
                for (int xc = - 1; xc <= 1; xc++)
                {
                    //Set the Gy matrix and the temporary colors variables
                    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
                    //Calculate the Gx value for each pixel
                    if ((yc + y) >= 0 && (yc + y) < (height) && (xc + x) >= 0 && (xc + x) < (width))
                    {
                        gy_red += (image_reference[yc + y][xc + x].rgbtRed) * gy[yc + 1][xc + 1];
                        gy_blue += (image_reference[yc + y][xc + x].rgbtBlue) * gy[yc + 1][xc + 1];
                        gy_green += (image_reference[yc + y][xc + x].rgbtGreen) * gy[yc + 1][xc + 1];
                    }
                }
            }
            //Calculate the pixel final value, using Sobel algorithm and capping to 255
            int tmp;
            tmp = round(sqrt((gx_red * gx_red) + (gy_red * gy_red)));
            if (tmp > 255)
            {
                image[y][x].rgbtRed = 255;
            }
            else
            {
                image[y][x].rgbtRed = tmp;
            }
            tmp = round(sqrt((gx_green * gx_green) + (gy_green * gy_green)));
            if (tmp > 255)
            {
                image[y][x].rgbtGreen = 255;
            }
            else
            {
                image[y][x].rgbtGreen = tmp;
            }
            tmp = round(sqrt((gx_blue * gx_blue) + (gy_blue * gy_blue)));
            if (tmp > 255)
            {
                image[y][x].rgbtBlue = 255;
            }
            else
            {
                image[y][x].rgbtBlue = tmp;
            }
        }
    }
    return;
}
