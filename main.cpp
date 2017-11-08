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
bool checkImage(vector<vector <Pixel> >&, vector<vector <Pixel> >&);
//Receives a pixel matrix then tallies the total value of red green and blue
void pixelValue(vector<vector <Pixel> > &,int, int, int &, int &, int &);
//Receive red green and blue averages and places them into a pixel matrix through reference 
void insertPixel(vector<vector <Pixel> > &, int, int, int, int, int, int);
void resizeCanvas(vector<vector<Pixel> > &, vector<vector<Pixel> > &);
const int FIRST_FILE = 0;
int main()
{
  int fileAmount = 0;
  vector<string> fileList;
  Bitmap img;
  Pixel rgb;
  string fileName;
  bool enterInput = true;
  vector< vector<Pixel> > originalMatrix;
  vector< vector<Pixel> > matrixToCheck;
  cout << "Enter up to 10 valid BMP files. Enter DONE when done.\n";
  while(enterInput)
  {
    cin >> fileName;
    cout << fileName << endl; 
    if(fileName == "DONE")
    {
      enterInput = false;
    }else{
      img.open(fileName);
      if(img.isImage())
      {
        if(fileAmount == FIRST_FILE)
        {
          originalMatrix = img.toPixelMatrix();
          fileList.push_back(fileName);  
          fileAmount++;
          // cout << "original matrix set\n"; 
        }else
        {
          matrixToCheck = img.toPixelMatrix();   
         // cout << "matrix #" << fileAmount << endl; 
          if(checkImage(matrixToCheck, originalMatrix))
          {
            fileList.push_back(fileName);
            //  cout << "File succesfully added\n";
            fileAmount ++; 
          }

        } 
      } 
    }     
  }

 vector<vector <Pixel> > canvas;
 resizeCanvas(canvas, originalMatrix);
 for(int i = 0; i < originalMatrix.size(); i++)
  {
    for(int j = 0; j < originalMatrix[i].size(); j++)
    {
      for(int k = 0; k < fileList[i].size(); k++)
      {
        int red = 0, green = 0, blue = 0;
        img.open(fileList[k]);
        vector< vector <Pixel> > valuesToGet = img.toPixelMatrix();
        pixelValue(valuesToGet, i, j, red, green, blue);
        cout << red << endl << green << endl << blue << endl; 
        insertPixel(canvas, i, j, red, green, blue, fileList.size()); 
      }
    }
  } 
  img.fromPixelMatrix(canvas);
  img.save("composite.bmp");
}

bool checkImage(vector<vector <Pixel> >& pixelMatrix, vector<vector <Pixel> >& originalMatrix)
{
  if(pixelMatrix.size() == originalMatrix.size())
  {
    for(int i = 0; i < pixelMatrix.size(); i++) 
    {
      for(int j = 0; j < pixelMatrix[i].size(); j++)
      {
        if(pixelMatrix[i].size() != originalMatrix[i].size())
        {
          cout << "Colums don't match\n";
          return false;
        }
      }
    }
  }else{
    cout << "rows no match\n";
    return false;
  }
  cout << "matrices match\n";
  return true;
}

void pixelValue(vector<vector <Pixel> >& pixelMatrix, int rows, int columns, int& redValue, int& greenValue, int& blueValue)
{
 Pixel values;
 values = pixelMatrix[rows][columns];
 redValue = redValue + values.red;
 greenValue = greenValue + values.green;
 blueValue = blueValue + values.blue;
}

void insertPixel(vector<vector <Pixel> >& canvasMatrix,int rows, int columns, int redAverage, int greenAverage, int blueAverage, int listSize)
{
  redAverage = redAverage / listSize;
  greenAverage = greenAverage / listSize;
  blueAverage = blueAverage / listSize;
  cout << "avg pixel calculated\n"; 
  Pixel rgb;
  rgb.red = redAverage;
  rgb.green = greenAverage;
  rgb.blue = blueAverage;
  cout << "pixel color set\n";
  canvasMatrix[rows][columns] = rgb;
  cout << "canvas pixels set\n"; 
}
void resizeCanvas(vector<vector <Pixel> >& canvas, vector<vector <Pixel> > original)
{
  for(int i = 0; i < original.size(); i++)
  {
    for(int j = 0; j < original[i].size(); i++)
    {
    }
  }
}
