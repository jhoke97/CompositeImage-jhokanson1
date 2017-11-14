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
//vector <vector <Pixel> >loadImage(Bitmap);

//Checks if image is a valid bitmap and if it's the same size as the original bitmap. If the bitmap image being loaded is the original image, skip the size check.
bool checkImage(vector<vector <Pixel> >&, vector<vector <Pixel> >&);

void averagePixel(vector<vector <Pixel> > &, int, int&, int&);

//Receive red green and blue averages and places them into a pixel matrix through reference 
void insertPixel(vector<vector <Pixel> >&, vector<vector <Pixel> >&, int&, int&);

vector< vector<Pixel> > resizeMatrix(vector<vector <Pixel> > &, vector<vector <Pixel> > &);

const int FIRST_FILE = 0;

int main()
{
  vector<string> fileList;
  Bitmap img;
  Pixel rgb;
  string fileName;
  bool enterInput = true;
  vector< vector<Pixel> > originalMatrix;
  vector< vector<Pixel> > matrixToCheck;
  vector <vector <Pixel> > canvas; 
  cout << "Enter up to 10 valid BMP files. Enter DONE when done.\n";
  while(enterInput)
  {
    cin >> fileName;
    if(fileName == "DONE" || fileList.size() >= 10)
    {
      enterInput = false;
    }else{
      img.open(fileName);
      if(img.isImage())
      {
        if(fileList.size() == FIRST_FILE)
        {
          originalMatrix = img.toPixelMatrix();
          fileList.push_back(fileName);  
        }else
        {
          matrixToCheck = img.toPixelMatrix();   
          if(checkImage(matrixToCheck, originalMatrix))
          {
            fileList.push_back(fileName);
          }

        } 
      } 
    }     
  }

  resizeMatrix(canvas, originalMatrix); 
  for(int i = 0; i < fileList.size(); i++)
  {
    img.open(fileList[i]);
    vector< vector <Pixel> > matrixToGet = img.toPixelMatrix(); 
    for(int j = 0; j < canvas.size(); j++)
    {
      for(int k = 0; k < canvas[j].size(); k++)
      {
        insertPixel(canvas, matrixToGet, j, k);  
      }
    } 
    cout<<"...and done.\n";
  }

    for(int j = 0; j < canvas.size(); j++)
    {
      for(int k = 0; k < canvas[j].size(); k++)
      {
        averagePixel(canvas, fileList.size(), j, k); 
      }
    }

  cout<<"Canvas is "<<canvas.size()<<"x"<<canvas[0].size()<<endl; 
  img.fromPixelMatrix(canvas);
  if(  img.isImage() )
  {
    cout<<"Saved.\n";
    img.save("composite.bmp");
  }
  else
  {
    cout<<"TROUBLE!\n";
  }

  return 0;  
}

bool checkImage(vector<vector <Pixel> >& pixelMatrix, vector<vector <Pixel> >& originalMatrix)
{
  if(pixelMatrix.size() == originalMatrix.size())
  {
    for(int i = 0; i < pixelMatrix.size(); i++) 
    {

      if(pixelMatrix[i].size() != originalMatrix[i].size())

        return false;
    }    
  }else{
    return false;
  }
  return true;
}

void insertPixel(vector<vector <Pixel> >& canvasMatrix, vector<vector <Pixel> >& valuesToGet, int& rows, int& columns)
{
  Pixel canvasRgb;
  Pixel getRgb;
  canvasRgb = canvasMatrix[rows][columns];
  getRgb = valuesToGet[rows][columns];
  canvasRgb.red = canvasRgb.red + getRgb.red;
  canvasRgb.green = canvasRgb.green + getRgb.green;
  canvasRgb.blue = canvasRgb.blue + getRgb.blue;
  canvasMatrix[rows][columns] = canvasRgb; 
}
void averagePixel(vector< vector<Pixel> >& canvasMatrix, int listSize, int& rows, int& columns)
{
  Pixel rgb;
  rgb = canvasMatrix[rows][columns]; 
  rgb.red = rgb.red / listSize;
  rgb.green = rgb.green / listSize;
  rgb.blue = rgb.blue / listSize; 
  canvasMatrix[rows][columns] = rgb; 
}

vector<vector <Pixel> > resizeMatrix(vector<vector<Pixel> >& canvas, vector<vector <Pixel> >& original)
{
  for(int i = 0; i < original.size(); i++)
  {

    canvas.resize(original.size()); 
    for(int j = 0; j < original[i].size(); i++)
    {
      canvas[i].resize(original[i].size()); 
    }
  }
  return canvas;
}
