#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
int main()
{
    Mat input = imread("origin.jpg",0);
    imshow("original image",input);
    int rows =input.rows;
    int cols = input.cols;
    int i,j;
    double number[256],p[256],sum[256];
    int imhist[256];
    sum[0]=0;
    
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            number[input.at<uchar>(i,j)]++;
        }
    }
    for(i=0; i<256; i++)
    {
        p[i]=number[i]/(double)(rows*cols);
    }
    sum[0]=p[0];
    
    for (i=1; i<256; i++) {
        sum[i]=sum[i-1]+p[i];
    }
    for (i=0; i<256; i++) {
        sum[i]=sum[i]*255;
        imhist[i]=(int)(sum[i]+0.5);
    }
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            input.at<uchar>(i,j)=imhist[input.at<uchar>(i,j)];
        }
    }
    
    imwrite("result.jpg", input);
    return 0;
}
 
 
