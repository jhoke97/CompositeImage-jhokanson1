#include <iostream>
#include <vector>
#include <string>
#include "bitmap.h"
using namespace std;

bool checkImage(vector<vector <Pixel> >&, vector<vector <Pixel> >&);
void averagePixel(vector<vector <Pixel> >&, int, int&, int&);
void insertPixel(vector<vector <Pixel> >&, vector<vector <Pixel> >&, int&, int&);
void resizeMatrix(vector<vector <Pixel> > &, vector<vector <Pixel> > &);

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
  if(fileList.size() > 1 )
  {
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
    cout<< "Image " << i + 1 << " of " << fileList.size() << " processed\n";
  }

  for(int j = 0; j < canvas.size(); j++)
  {
    for(int k = 0; k < canvas[j].size(); k++)
    {
      averagePixel(canvas, fileList.size(), j, k); 
    }
  }
  img.fromPixelMatrix(canvas);
  img.save("composite-jhokanson1");
  }else{
    cout << "Composite Image could not be created\n";
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
        cout << "The BMP file is not the same size as the original image\n";
        return false;
    }    
  }else{
    cout << "The BMP file is not the same size as the original image.\n";
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

void resizeMatrix(vector<vector<Pixel> >& canvas, vector<vector <Pixel> >& original)
{
  for(int i = 0; i < original.size(); i++)
  {

    canvas.resize(original.size()); 
    for(int j = 0; j < original[i].size(); j++)
    {
      canvas[i].resize(original[i].size()); 
    }
  }


}

