#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include<iostream>
using namespace cv;

int main()
{Mat image = imread("origin.jpg",0);
if(!image.data)
{
    printf( "image read is error!") ;
    return 0;
}
imshow("Original Image", image);
Mat imagetmp = image.clone();
int M= image.rows;
int N = image.cols * image.channels();
int rang_min, rang_max;
for(int n = 1; n <= 8; n ++)
{
    rang_min = pow(2, n - 1);
    rang_max = pow(2, n);
      for(int i= 0; i< M; i ++)
    {
         uchar*data = image.ptr<uchar>(i);
         uchar*datatmp = imagetmp.ptr<uchar>(i);
           for(int j= 0; j< N; j++)
          {
              if(data[j] >= rang_min && data[j] < rang_max)
                datatmp[j] = 255;
              else  datatmp[j] = 0;
           }
      }
      switch (n)
    {
        case 1:imshow("Bit Level 1", imagetmp);break;
        case 2:imshow("Bit Level 2", imagetmp);break;
        case 3:imshow("Bit Level 3", imagetmp);break;
        case 4:imshow("Bit Level 4", imagetmp);break;
        case 5:imshow("Bit Level 5", imagetmp);break;
        case 6:imshow("Bit Level 6", imagetmp);break;
        case 7:imshow("Bit Level 7", imagetmp);break;
        case 8:imshow("Bit Level 8", imagetmp);break;
     }

}
waitKey(0);
}





