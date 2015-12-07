#include "opencv2/core.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include<iostream>
#include<string.h>
#include<stdio.h>

using namespace cv;
using namespace std;

void localhistogram(Mat &tmpimage,int i,int j,int hist[])
{ int a,b,x;
  int k;
  k=tmpimage.at<uchar>(i,j);
 for(x=0;x<256;x++)
 {hist[x]=0;}
 for(a=i-1;a<=i+1;a++)
 {    for(b=j-1;b<=j+1;b++)
     {
      hist[tmpimage.at<uchar>(a,b)]++;
     }
 }
 for(x=1;x<k+1;x++)
   {hist[x]=hist[x]+hist[x-1];}
}
void localhistogrameq(Mat &image)
{ 
   Mat tmpimage;
   if(!image.data)
   {cout<<"fail to load image."<<endl;}
   imshow("origin",image);
   copyMakeBorder(image,tmpimage,1,1,1,1,BORDER_CONSTANT,0);
   int m=tmpimage.rows;
   int n=tmpimage.cols;
   int hist[256];
   for(int i=1;i<m-1;i++)
  {
     for(int j=1;j<n-1;j++)
    {
      localhistogram(tmpimage,i,j,hist);  
      image.at<uchar>(i-1,j-1)=static_cast<int>(255*hist[tmpimage.at<uchar>(i,j)]/9);
    }
  }
  imshow("processed image",image);
  
 }
int main(int argc, char *argv[])
{
   Mat image;
   Mat dstimage;
   if(argc>2)
  {
      switch(argv[1][1])
     {
      case 'i':
               image=imread(argv[2],0);
               imshow("origin",image);                 
               break;
      case 'o':   
               image=imread(argv[2],0);
               localhistogrameq(image);
               break;
     }
   } 
  

  waitKey(0);
  return 0;
}

