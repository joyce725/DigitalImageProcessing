#include "opencv2/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include<iostream>
#include <fstream> 
#include<vector>
using namespace cv;
using namespace std;


int main(int argc, char* argv[])
{
    Mat groundtruthImage,segmentationImage;
    groundtruthImage = imread("image1.bmp",0);
    segmentationImage = imread("image2.bmp",0);
    Mat outputImage;
    outputImage=groundtruthImage.clone();
    if(!(groundtruthImage.data && segmentationImage.data))
    {
        cout<<"fail to load image."<<endl;
        return 0;
    }
    int rowNumber=outputImage.rows;
    int colNumber=outputImage.cols;
    
    for(int i =0; i< rowNumber; i++)
    {
        for(int j=0; j<colNumber; j++)
        {
            if(groundtruthImage.at<uchar>(i,j)!=segmentationImage.at<uchar>(i,j))
                outputImage.at<uchar>(i,j)=255;
        }
    }
    imwrite("result.bmp",outputImage);
    return 0;
}