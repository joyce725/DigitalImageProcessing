#include "opencv2/core.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include<iostream>
using namespace cv;
using namespace std;
int main()
{
    Mat image=imread("origin.jpg",0);
   imshow("origin",image);
   if(!image.data){ printf("Can not load image");return -1;}
   //定义变量
   MatND  dstHist;   //在cv中用CvHistogram *hist=cvCreateHist
   int dims=1;
   float hranges[]={0,255};
   const float*ranges[]={hranges};
   int size=256;
   int channels=0;
   //计算图像的直方图
   calcHist(&image,//输入的数组
              1, //数组个数为1
              &channels,//通道索引
                   Mat(), //不使用掩膜
                dstHist,//输出的目标直方图
                    dims,//需要计算的直方图维数
                    &size,//存放维度的直方图尺寸的数组
                    ranges);//每一维数值的取值范围的数组
   int scale=1;
   Mat dstimage(size*scale,size,CV_8U,Scalar(0));
   //获取最大值和最小值
   double minValue=0;
   double maxValue=0;
   minMaxLoc(dstHist,&minValue,&maxValue,0,0);
   //cvGetMinMaxHistValue()
   int hpt=saturate_cast<int>(0.9*size);//设置最大峰值为图像高度的90%
   for(int i=0;i<256;i++)
   {
       float binValue=dstHist.at<float>(i); //注意hist中是float，获取直方图直条的值
       int  realValue=saturate_cast<int>(binValue*hpt/maxValue);//绘制直方图的高度
      //正式进行绘制
       rectangle(dstimage,Point(i*scale,size-1),Point((i+1)*scale-1,size-realValue),Scalar(255));
    }
imshow("histogram",dstimage);
   waitKey(0);
   return 0;
  }

