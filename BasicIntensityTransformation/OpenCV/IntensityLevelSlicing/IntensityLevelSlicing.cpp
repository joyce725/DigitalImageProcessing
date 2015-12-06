#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include<iostream>
using namespace cv;

int main()
{
    Mat image = imread("origin.jpg");
      if(!image.data)
      {
           printf("image read is error!" ) ;
        return 0;
       }
imshow("Original Image", image);
int min = 150;
int M= image.rows;
int N = image.cols * image.channels();
for(int i= 0; i< M; i++)
{
    uchar *data =image.ptr<uchar>(i);
for(int j= 0; j< N; j++)
{
  if(data[j] >min)
    data[j] = 255;
else data[j] = 0;
}
}
imshow("Processed Image", image);

waitKey(0);
}



