#include <iostream>
#include <vector>
#include <string>
#include "bitmap.h"
using namespace std;
//Prompt user to enter bitmap files
//Load each bitmap into a pixel matrix
//Check that each bitmap image loaded is a valid format and the same size
//Get the average value of red, green and blue of each pixel from each matrix
//Push the average pixel color into a new pixel matrix
//Save the new pixel matrix 

//Receives a bitmap image and returns a pixel matrix 
vector <vector <Pixel> >loadImage(Bitmap);
//Checks if image is a valid bitmap and if it's the same size as the original bitmap. If the bitmap image being loaded is the original image, skip the size check.
bool checkImage(vector<vector <Pixel> >);
//Receives a pixel matrix then tallies the total value of red green and blue
void pixelValue(vector<vector <Pixel> > &, int &, int &, int &);
//Receive red green and blue averages and places them into a pixel matrix through reference 
void insertPixel(vector<vector <Pixel> > &, int, int, int);
int main()
{
}
