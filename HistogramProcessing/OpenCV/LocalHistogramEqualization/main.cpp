#include "opencv2/core.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include<iostream>
using namespace cv;
using namespace std;
void histeq(Mat &image,int i,int j,int hist[])
{ int a,b,x;
  int k;
  k=image.at<uchar>(i,j);
 for(x=0;x<256;x++)
 {hist[x]=0;}
 for(a=i-1;a<=i+1;a++)
 {    for(b=j-1;b<=j+1;b++)
     {
      hist[image.at<uchar>(a,b)]++;
     }
 }
 for(x=1;x<k+1;x++)
   {hist[x]=hist[x]+hist[x-1];}
}
int main()
{Mat image=imread("origin.tif",0);
 Mat dst;
 if(!image.data)
 {cout<<"fail to load image."<<endl;return 0;}
 imshow("origin",image);
 copyMakeBorder(image,dst,1,1,1,1,BORDER_CONSTANT,0);
 int m=dst.rows;
 int n=dst.cols;
 int hist[256];
 int i,j;
 for(i=1;i<m-1;i++)
{
 for(j=1;j<n-1;j++)
 {
  histeq(dst,i,j,hist);  
  image.at<uchar>(i-1,j-1)=static_cast<int>(255*hist[dst.at<uchar>(i,j)]/9);
 }
}

imshow("processed image",image);
waitKey(0);
return 0;
}

