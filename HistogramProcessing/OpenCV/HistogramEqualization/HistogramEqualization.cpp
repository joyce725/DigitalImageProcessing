#include "opencv2/core.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include<iostream>
using namespace cv;
using namespace std;

int main()
{Mat image=imread("origin.jpg",0);
 imshow("origin",image);
 if(!image.data){cout<<"fail to load image"<<endl;return 0;}
 MatND imhist;
 int dims=1;
 float hranges[]={0,255};
 const float *ranges[]={hranges};
 int size=256;
 int channels=0;
 int M=image.rows;
 int N=image.cols*image.channels();
 int total=M*N;
 int i,j;
 int tmp;
 calcHist(&image,1,&channels,Mat(),imhist,dims,&size,ranges);
 //计算已知图像的直方图
 for(i=1;i<256;i++)
 {
  imhist.at<float>(i)=imhist.at<float>(i)+imhist.at<float>(i-1);
 } //对直方图中的值进行叠加,直方图的值表示的是不同灰度级的像素
 for(i=0;i<M;i++)
{
  uchar *data=image.ptr<uchar>(i);
 for(j=0;j<N;j++)
 { tmp=static_cast<int>(255* imhist.at<float>(data[j])/total);
  if(data[j]<0) data[j]=0;
  else if(data[j]>255) data[j]=255;
  else data[j]=tmp;
 }  //对灰度值进行映射
}
imshow("processed image",image);
waitKey(0);

}
 
 
