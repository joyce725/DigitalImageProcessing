#include "opencv2/core.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include<iostream>
using namespace cv;
using namespace std;


void calculate(Mat& image,int i,int j,double *m1,double *u1)
{
 int a,b;
 int data[9];
 int n=0;
 int sum=0;
 double var=0;
  
 for(a=-1;a<2;a++)
{
  for(b=-1;b<2;b++)
 {
  data[n]=image.at<uchar>(i+a,j+b);
  sum+=data[n];
  n++;
 }
}
*m1=sum/9;//计算3*3领域局部均值
for(n=0;n<9;n++)
{
 var+=pow(data[n]-*m1,2);
}
*u1=sqrt(var/9);//计算3*3领域局部标准差

}

int main()
{  
 Mat image=imread("origin.png",0);
 if(!image.data)
 {cout<<"fail to load image."<<endl;return 0;}
 imshow("origin",image);
 Mat output;
 output=image.clone();

int i,j;
int M=image.rows;
int N=image.cols;
int total=M*N;
double sum=0,var=0;
double m,u;

for(i=0;i<M;i++)
{
 for(j=0;j<N;j++)
 {
  sum+=image.at<uchar>(i,j);
 }
}
m=sum/total;//计算全局均值

for(i=0;i<M;i++)
{
 for(j=0;j<N;j++)
 {
  var+=pow(image.at<uchar>(i,j)-m,2);
 }
}
u=sqrt(var/total);//计算全局标准差

double m1,u1;
for(i=1;i<M-1;i++)
{
 for(j=1;j<N-1;j++)
 {
  calculate(image,i,j,&m1,&u1);
 if(m1<=0.4*m&&u1>=0.02*u&&u1<=0.4*u)
  {output.at<uchar>(i,j)=4*output.at<uchar>(i,j);}
 }
}

imshow("processed image",output);
waitKey(0);
return 0;
}










 
