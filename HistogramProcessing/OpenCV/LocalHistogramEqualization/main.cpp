#include "opencv2/core.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
using namespace cv;
using namespace std;

void localHistogram(Mat &inputImage,int i,int j,int s,int inputHistogram[])
{ int a,b,x;
  int inputValue;
  inputValue = inputImage.at<uchar>(i,j);
  for(x = 0;x < 256;x++)
  { 
   inputHistogram[x] = 0;
  }
  for(a = i - s;a <=i + s;a++)
  {    
     for(b=j - s;b<=j + s;b++)
     {
      inputHistogram[inputImage.at<uchar>(a,b)]++;
     }
  }
 for(x = 1;x < inputValue + 1;x++)
 {
    inputHistogram[x] = inputHistogram[x] + inputHistogram[x-1];
 }
}
 
int main(int argc, char *argv[])
{
   Mat srcImage;
   Mat inputImage;
   int sizeNum;
   srcImage = imread(argv[2],0) ;
   if(!srcImage.data)
   {
     cout<<"fail to load image."<<endl;
   }
   sizeNum=atoi(argv[6]);
   int s = (sizeNum - 1)/2;
   int total = sizeNum*sizeNum;
   copyMakeBorder(srcImage,inputImage,s,s,s,s,BORDER_CONSTANT,0);
   int rowNumber = inputImage.rows;
   int colNumber = inputImage.cols;
   int inputHistogram[256];
   for(int i = s;i < rowNumber - s;i++)
  {
      for(int j = s;j < colNumber - s;j++)
      {
       localHistogram(inputImage,i,j,s,inputHistogram);  
       srcImage.at<uchar>(i-s,j-s) = static_cast<int>(255*inputHistogram[inputImage.at<uchar>(i,j)]/total);
      }
  }
   imwrite(argv[4],srcImage); 
   waitKey(0);
   return 0;
}


