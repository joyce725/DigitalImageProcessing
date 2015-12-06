#include "opencv2/core.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include<iostream>
using namespace cv;
using namespace std;

 
int main()
{
 Mat image=imread("origin.jpg",0);
 Mat tempimage;
 image.copyTo(tempimage); 
 if(!image.data){cout<<"fail to load image."<<endl;return 0;}
 MatND imhist;
 int dims=1;
 float hranges[]={0,255};
 const float *ranges[]={hranges};
 int size=256;
 int channels=0;
 calcHist(&tempimage,1,&channels,Mat(),imhist,dims,&size,ranges);
//计算图像的直方图
 
 double m1,sig1,m2,sig2,A1,A2,k;
 m1=0.15;
 sig1=0.05;
 m2=0.75;
 sig2=0.05;
 A1=1;
 A2=0.07;
 k=0.002;
 double gauss[256]={0};
 double c1=A1*(1.0/(sqrt(2*CV_PI))*sig1);
 double k1=2*sig1*sig1;
 double c2=A2*(1.0/(sqrt(2*CV_PI))*sig2);
 double k2=2*sig2*sig2;
 double z=0.0,tmp=0.0,p=0.0;
 for(int i=0;i<256;i++) 
 {
  tmp=k+c1*exp(-(z-m1)*(z-m1)/k1)+c2*exp(-(z-m2)*(z-m2)/k2);
  gauss[i]=tmp;
  p=p+tmp;
  z=z+1.0/256;
 }//双峰值高斯函数
 for(int i=0;i<256;i++)
 {
  gauss[i]=gauss[i]/p;
 } //对双峰值高斯函数进行归一化操作

double G[256]={0};
double S[256]={0};
double vin1=0,vin2=0;
int M=tempimage.rows;
int N=tempimage.cols*tempimage.channels();
int total=M*N;

for(int i=0;i<256;i++)
{
vin1=gauss[i]+vin1;
vin2=imhist.at<float>(i)+vin2;
G[i]=255*vin1;
S[i]=255*vin2/total; 
}//分别对归一化的双峰值高斯函数和给定直方图进行均衡化操作

int index;
int T[256]={0};
double minvalue,value;

for(int m=0;m<256;m++)
{
  for(int n=0;n<256;n++)
  { 
    value=fabs(G[n]-S[m]);  
    if(value<1)
    {
     minvalue=value;
     index=n;
    }
  }
T[m]=index;
}//寻找与S最接近的G值，并建立相应的映射关系
for(int x=0;x<M;x++)
{
 uchar *data=tempimage.ptr<uchar>(x);
 for(int y=0;y<N;y++)
 {
   data[y]=T[data[y]];
 }
}
//实现最终映射关系
imshow("origin",image);
imshow("processed image",tempimage);
waitKey(0);
return 0;
}

