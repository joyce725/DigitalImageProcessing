#include "opencv2/core.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include<iostream>
#include<string.h>
#include<stdio.h>

using namespace cv;
using namespace std;

void localhistogram(Mat &tmpimage,int i,int j,int s,int hist[])
{ int a,b,x;
  int k;
  k=tmpimage.at<uchar>(i,j);
 for(x=0;x<256;x++)
 {hist[x]=0;}
 for(a=i-s;a<=i+s;a++)
 {    for(b=j-s;b<=j+s;b++)
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
   cout<<"Enter the size of neighborhood:"<<endl;
   int size;
   cin>>size;
   int s=(size-1)/2;
   int total=size*size;
   copyMakeBorder(image,tmpimage,s,s,s,s,BORDER_CONSTANT,0);
   int m=tmpimage.rows;
   int n=tmpimage.cols;
   int hist[256];
   for(int i=s;i<m-s;i++)
  {
     for(int j=s;j<n-s;j++)
    {
      localhistogram(tmpimage,i,j,s,hist);  
      image.at<uchar>(i-s,j-s)=static_cast<int>(255*hist[tmpimage.at<uchar>(i,j)]/total);
    }
  }
  imshow("processed image",image);
  
 }
int main(int argc, char *argv[])
{
   Mat image;
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

