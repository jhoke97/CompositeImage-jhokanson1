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
void pixelValue(vector<vector <Pixel> > &, int &, int &, int &);
//Receive red green and blue averages and places them into a pixel matrix through reference 
void insertPixel(vector<vector <Pixel> > &, int, int, int);
const int FIRST_FILE = 1;
int main()
{
  int fileAmount = 0;
  string fileName;
  vector<string> fileList;
  Bitmap img;
  Pixel rgb;
  vector< vector<Pixel> > originalMatrix;
  vector< vector<Pixel> > matrixToCheck;
  cout << "Enter up to 10 valid BMP files. Enter DONE when done.\n";
  do{
    cin >> fileName;
    img.open(fileName);
    fileAmount++;
    if(img.isImage())
    {
      if(fileAmount == FIRST_FILE)
      {
        originalMatrix = img.toPixelMatrix();
        cout << "original matrix set\n"; 
      }else
      {
        matrixToCheck = img.toPixelMatrix();   
        cout << "matrix #" << fileAmount << endl; 
      }
      if(fileAmount != FIRST_FILE)
      {
        if(checkImage(matrixToCheck, originalMatrix))
        {
          fileList.push_back(fileName);
          cout << "File succesfully added\n";
        }

      } 
    }     
  }while(fileName != "DONE" || fileName != "done" || fileName != "Done" || fileAmount == 10);
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
