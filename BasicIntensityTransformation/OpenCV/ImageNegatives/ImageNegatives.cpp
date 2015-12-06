#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include<iostream>
using namespace cv;

void neg(Mat&input,Mat &output)
{   output=input.clone();  //复制实参到临时变量
    int m=output.rows;    //行数
    int n =output.cols*output.channels();   //列数X通道数=每一行元素的个数
    //双重循环，遍历所有的像素值
    for(int i=0;i<m;i++)  //行循环
    {
        uchar*data=output.ptr<uchar>(i);  //获取第i行的首地址
             for(int j=0;j<n;j++)   //列循环
            {
               data[j]=data[j]*(-1)+255;
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
Mat negimage;
negimage.create( image.rows,image.cols,image.type() );
//效果图的大小、类型与原图片相同
neg(image,negimage);
imshow("processed image",negimage);
imwrite("processed.jpg",negimage);
waitKey(0);
}

