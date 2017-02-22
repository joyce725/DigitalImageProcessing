#include "opencv2/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

void myDFT(Mat &src, int M, int N, double** R, double** I)
{
    
    int x, y, u, v;
    double grayValue;
    double ang;
    
    for (u = 0; u<M; u++){
        for (v = 0; v<N; v++){
            R[u][v] = 0.0;
            I[u][v] = 0.0;
            for (x = 0; x<M; x++){
                for (y = 0; y<N; y++){
                    grayValue = src.at<uchar>(x, y);
                    ang = 2 * M_PI*((double)x*u / (double)M + (double)y*v / (double)N);
                    R[u][v] += cos(ang)*grayValue;
                    I[u][v] += -sin(ang)*grayValue;
                }
            }
            
            /*real.at<uchar>(u, v) = R[u][v];
            imagin.at<uchar>(u, v) = I[u][v];*/
        }
    }
    
}
void myIDFT(int M, int N, double** r, double** i,  double** R1, double** I1, double** R2, double** I2)
{
    int x, y, u, v;
    double phase;
    double ang;
    
    for(x=0;x<M;x++){
        for(y=0;y<N;y++){
            r[x][y]=0.0;
            i[x][y]=0.0;
            for(u=0;u<M;u++){
                for(v=0;v<N;v++){
                    ang=2*M_PI*((double)x*u/(double)M+(double)y*v/(double)N);
                    phase=atan2(I1[u][v],R1[u][v]);
                    r[x][y]+=sqrt(R2[u][v] * R2[u][v] + I2[u][v] * I2[u][v])*cos(phase+ang);
                    i[x][y]+=sqrt(R2[u][v] * R2[u][v] + I2[u][v] * I2[u][v])*sin(phase+ang);
                    
                }
            }
            /*real.at<uchar>(x,y)=r[x][y]/(M*N);
            imagin.at<uchar>(x,y)=i[x][y]/(M*N);*/
        }
    }
}


int main(int argc, char* argv[])
{
	Mat src1, src2;
	src1 = imread("test.bmp", 0);
	src2 = imread("test.png", 0);
    
	int x, y, u, v;
	int M, N;
	
    M = src1.rows;
	N = src1.cols;
    //频谱重构，两图像的宽高必须一致
	
    Mat dft_mag1(M, N, CV_8UC1, Scalar::all(0));
    Mat dft_phase1(M, N, CV_8UC1, Scalar::all(0));
    Mat dft_mag2(M, N, CV_8UC1, Scalar::all(0));
    Mat dft_phase2(M, N, CV_8UC1, Scalar::all(0));
    Mat idft1(M, N, CV_8UC1, Scalar::all(0));
    Mat idft2(M, N, CV_8UC1, Scalar::all(0));
    
    double** R1, **I1, **R2, **I2;
	R1 = new double*[M];
    I1 = new double*[M];
    R2 = new double*[M];
    I2 = new double*[M];
	for (x = 0; x<M; x++){
		R1[x] = new double[N];
		I1[x] = new double[N];
        R2[x] = new double[N];
        I2[x] = new double[N];
		for (y = 0; y<N; y++){
			R1[x][y] = 0;
			I1[x][y] = 0;
            R2[x][y] = 0;
            I2[x][y] = 0;
			src1.at<uchar>(x, y) = pow(-1, x+y)*src1.at<uchar>(x, y);
            src2.at<uchar>(x, y) = pow(-1, x+y)*src2.at<uchar>(x, y);  //shift
		}
	}

    
    myDFT(src1, M, N, R1, I1);
    myDFT(src2, M, N, R2, I2);
    
    //Phase map
    for (u = 0; u<M; u++){
        for (v = 0; v<N; v++){
            dft_phase1.at<uchar>(u, v)=(atan2(I1[u][v],R1[u][v])/(double)(2*M_PI))*255;
            dft_phase2.at<uchar>(u, v)=(atan2(I2[u][v],R2[u][v])/(double)(2*M_PI))*255;

        }
    }
    imwrite("dft_phase1.png",dft_phase1);
    imwrite("dft_phase2.png",dft_phase2);
    
    
    
    //Amplitude map(normalization)
   	double max_dst1 = 0;
    for (u = 0; u<M; u++){
        for (v = 0; v<N; v++){
            dft_mag1.at<uchar>(u, v) = (int)log(1 + sqrt(R1[u][v] * R1[u][v] + I1[u][v] * I1[u][v]));
            if (max_dst1 < dft_mag1.at<uchar>(u, v))
                max_dst1 = dft_mag1.at<uchar>(u, v);
        }
    }
    
    for (u = 0; u < M; u++){
        for (v = 0; v < N; v++)
        {
            dft_mag1.at<uchar>(u, v) *= 255.0/max_dst1;
        }
    }
    imwrite("dft_mag1.png", dft_mag1);
    
    double max_dst2 = 0;
    for (u = 0; u<M; u++){
        for (v = 0; v<N; v++){
            dft_mag2.at<uchar>(u, v) = (int)log(1 + sqrt(R2[u][v] * R2[u][v] + I2[u][v] * I2[u][v]));
            if (max_dst2 < dft_mag2.at<uchar>(u, v))
                max_dst2 = dft_mag2.at<uchar>(u, v);
        }
    }
    
    for (u = 0; u < M; u++){
        for (v = 0; v < N; v++)
        {
            dft_mag2.at<uchar>(u, v) *= 255.0/max_dst2;
        }
    }
    imwrite("dft_mag2.png", dft_mag2);


    //IDFT
    
   
    double** r1, **i1, **r2, **i2;
    r1 = new double*[M];
    i1 = new double*[M]; //amplitude map of src1 + phase map of src2
    r2 = new double*[M]; //amplitude map of src2 + phase map of src1
    i2 = new double*[M];
    for(x=0;x<M;x++){
        r1[x]=new double[N];
        i1[x]=new double[N];
        r2[x]=new double[N];
        i2[x]=new double[N];
    }
    

    myIDFT(M, N, r1, i1, R2, I2, R1, I1);
    myIDFT(M, N, r2, i2, R1, I1, R2, I2);
    
    for(x=0;x<M;x++){
        for(y=0;y<N;y++){
            idft1.at<uchar>(x,y) =sqrt(r1[x][y] * r1[x][y] + i1[x][y] * i1[x][y]);
            idft2.at<uchar>(x,y) =sqrt(r2[x][y] * r2[x][y] + i2[x][y] * i2[x][y]);
        }
    }
    imwrite("idft1.bmp",idft1);
    imwrite("idft2.bmp",idft2);
  
    for(x=0;x<M;x++){
        for(y=0;y<N;y++){
            idft1.at<uchar>(x, y)= pow(-1, x+y)*sqrt(r1[x][y] * r1[x][y] + i1[x][y] * i1[x][y])/(M*N);
            idft2.at<uchar>(x, y) = pow(-1, x+y)*sqrt(r2[x][y] * r2[x][y] + i2[x][y] * i2[x][y])/(M*N);

        }
    }
    imwrite("idft_shift1.png",idft1);
    imwrite("idft_shift2.png",idft2);

	return 0;

}