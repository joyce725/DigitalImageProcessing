#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include<iostream>
using namespace cv;

void logtrans(Mat&input,Mat&output)
    { int M = input.rows;
    int N = input.cols;
    double gray ;
    for(int i = 0;i < M;i++)
   {
        for(int j = 0; j < N; j++)
        {
            gray = input.at<uchar>(i,j);
            gray = 32*log(1+(double)(gray));
            output.at<uchar>(i,j) =gray;
        }
    }
}
int main( )
{
Mat image  =  imread("origin.jpg",0);
if(!image.data)
{
        printf("Can not load image");return -1;
}
imshow("origin image",image);
Mat logimage;
logimage.create( image.rows,image.cols,image.type());
logtrans(image,logimage);
imshow("processed image",logimage);
waitKey(0);
}

