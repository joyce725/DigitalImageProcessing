#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include<iostream>
using namespace cv;

void gamtrans(Mat&input,Mat&output,double gamma)
    {
    int M =input.rows;
    int N = input.cols;
    double gray ;
    for(int i = 0;i < M;i++)
        {
          for(int j = 0; j < N; j++)
           {
            gray = input.at<uchar>(i,j);
            gray = pow( gray /255, gamma)*255;
            output.at<uchar>(i,j) =gray;
           }
    }
    }

int main( )
{ double gamma;
Mat image  =  imread("origin.jpg",0);
if(!image.data)
{
        printf("Can not load image");return -1;
}
printf("Please input the gamma value.Note that if gamma<1,you will get a lighter image.unless you will get a darker one. Besides,if gamma=1,the processed image will be the same as the origin one.");
scanf("%lf",&gamma);
imshow("origin image",image);
Mat gamimage;
gamimage.create( image.rows,image.cols,image.type() );
gamtrans(image,gamimage,gamma);
imshow("processed image",gamimage);
waitKey(0);
}

