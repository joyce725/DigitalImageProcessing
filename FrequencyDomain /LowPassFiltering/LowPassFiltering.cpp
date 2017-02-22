#include "opencv2/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

static double Distance(int x, int y, int c_x, int c_y){
    return sqrt((x-c_x)*(x-c_x)+(y-c_y)*(y-c_y));
}

void IdealLPFilter(double **LPF, int M, int N, double cut_off_frequency)
{
    double distance;
    int center_x=M/2;
    int center_y=N/2;
    for(int u=0;u<M;u++)
        for(int v=0;v<N;v++){
            distance=Distance(u,v,center_x,center_y);
            if(distance<=cut_off_frequency)
                LPF[u][v]=1.0;
            else
                LPF[u][v]=0.0;
        }
    
}
void ButterworthLPfilter(double **Butter, int M, int N,double cut_off_frequency,int n)
{
    double value;
    int center_x=M/2;
    int center_y=N/2;
    for(int u=0;u<M;u++)
        for(int v=0;v<N;v++){
                value=pow((Distance(u, v, center_x, center_y)/cut_off_frequency),2*n);
                Butter[u][v]=1/(1+value);
        }
}
void GaussianLPFilter(double **Gussian,int M,int N,double cut_off_frequency)
{
    double value;
    int center_x=M/2;
    int center_y=N/2;
    for(int u=0;u<M;u++)
        for(int v=0;v<N;v++){
            value=Distance(u, v, center_x, center_y);
            Gussian[u][v]=exp(-value*value/(2*cut_off_frequency*cut_off_frequency));
        }
}

void MatrixMulti(double** Filter, double** R, double**I, double** Filter_R, double** Filter_I, int M, int N)
{
    for(int u=0;u<M;u++)
        for(int v=0;v<N;v++){
            Filter_R[u][v]=Filter[u][v]*R[u][v];
            Filter_I[u][v]=Filter[u][v]*I[u][v];

    }
}

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
void myIDFT(int M, int N, double** r, double** i,  double** R, double** I)
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
                    phase=atan2(I[u][v],R[u][v]);
                    r[x][y]+=sqrt(R[u][v] * R[u][v] + I[u][v] * I[u][v])*cos(phase+ang);
                    i[x][y]+=sqrt(R[u][v] * R[u][v] + I[u][v] * I[u][v])*sin(phase+ang);
                    
                }
            }
            /*real.at<uchar>(x,y)=r[x][y]/(M*N);
             imagin.at<uchar>(x,y)=i[x][y]/(M*N);*/
        }
    }
}


int main(int argc, char* argv[])
{
    Mat src;
    src = imread("test.bmp", 0);
    
    int x, y, u, v;
    int M, N;
    
    M = src.rows;
    N = src.cols;
    
    Mat LPF_idft(M, N, CV_8UC1, Scalar::all(0));
    Mat Butter_idft(M, N, CV_8UC1, Scalar::all(0));
    Mat Gussian_idft(M, N, CV_8UC1, Scalar::all(0));
    Mat LPF_idft_shift(M, N, CV_8UC1, Scalar::all(0));
    Mat Butter_idft_shift(M, N, CV_8UC1, Scalar::all(0));
    Mat Gussian_idft_shift(M, N, CV_8UC1, Scalar::all(0));
    Mat lpf(M, N, CV_8UC1, Scalar::all(0));
    Mat butter(M, N, CV_8UC1, Scalar::all(0));
    Mat gussian(M, N, CV_8UC1, Scalar::all(0));
    
    double** R, **I;
    R = new double*[M];
    I = new double*[M];
    for (x = 0; x<M; x++){
        R[x] = new double[N];
        I[x] = new double[N];
        for (y = 0; y<N; y++){
            R[x][y] = 0;
            I[x][y] = 0;
            src.at<uchar>(x, y) = pow(-1, x+y)*src.at<uchar>(x, y);  //shift
        }
    }
    
    myDFT(src, M, N, R, I);
    
    double** LPF, **Butter, **Gussian;
    LPF= new double*[M];
    Butter = new double*[M];
    Gussian = new double*[M];
    for (x = 0; x<M; x++){
        LPF[x] = new double[N];
        Butter[x] = new double[N];
        Gussian[x] = new double[N];
    }

    double** LPF_R, **LPF_I, **Butter_R, **Butter_I, **Gussian_R, **Gussian_I;
    LPF_R = new double*[M];
    LPF_I = new double*[M];
    Butter_R = new double*[M];
    Butter_I = new double*[M];
    Gussian_R = new double*[M];
    Gussian_I = new double*[M];
    for (x = 0; x<M; x++){
        LPF_R[x] = new double[N];
        LPF_I[x] = new double[N];
        Butter_R[x] = new double[N];
        Butter_I[x] = new double[N];
        Gussian_R[x] = new double[N];
        Gussian_I[x] = new double[N];
    }
    
    double cut_off_frequency=10;
    IdealLPFilter(LPF, M, N, cut_off_frequency);
    ButterworthLPfilter(Butter, M, N, cut_off_frequency, 2);
    GaussianLPFilter(Gussian, M, N, cut_off_frequency);
    
    for (u = 0; u<M; u++){
        for (v = 0; v<N; v++){
            
            lpf.at<uchar>(u, v) = LPF[u][v]*255;
            butter.at<uchar>(u, v) = Butter[u][v]*255;
            gussian.at<uchar>(u, v) = Gussian[u][v]*255;
        }
    }
    imwrite("lpf.bmp",lpf);
    imwrite("butter.bmp",butter);
    imwrite("gussian.bmp",gussian);
    
    
    MatrixMulti(LPF, R, I, LPF_R, LPF_I, M, N);
    MatrixMulti(Butter, R, I, Butter_R, Butter_I, M, N);
    MatrixMulti(Gussian, R, I, Gussian_R, Gussian_I, M, N);
    
    //IDFT
    double** LPF_r, **LPF_i, **Butter_r, **Butter_i, **Gussian_r, **Gussian_i;
    LPF_r = new double*[M];
    LPF_i = new double*[M];
    Butter_r = new double*[M];
    Butter_i = new double*[M];
    Gussian_r = new double*[M];
    Gussian_i = new double*[M];
    for (x = 0; x<M; x++){
        LPF_r[x] = new double[N];
        LPF_i[x] = new double[N];
        Butter_r[x] = new double[N];
        Butter_i[x] = new double[N];
        Gussian_r[x] = new double[N];
        Gussian_i[x] = new double[N];
    }
    
    myIDFT(M, N, LPF_r, LPF_i, LPF_R, LPF_I);
    myIDFT(M, N, Butter_r, Butter_i, Butter_R, Butter_I);
    myIDFT(M, N, Gussian_r, Gussian_i, Gussian_R, Gussian_I);
    
    for(x=0;x<M;x++){
        for(y=0;y<N;y++){
            LPF_idft_shift.at<uchar>(x, y) = pow(-1, x+y)*sqrt(LPF_r[x][y] * LPF_r[x][y] + LPF_i[x][y] * LPF_i[x][y])/(M*N);
            Butter_idft_shift.at<uchar>(x, y) = pow(-1, x+y)*sqrt(Butter_r[x][y] * Butter_r[x][y] + Butter_i[x][y] * Butter_i[x][y])/(M*N);
            Gussian_idft_shift.at<uchar>(x, y) = pow(-1, x+y)*sqrt(Gussian_r[x][y] * Gussian_r[x][y] + Gussian_i[x][y] * Gussian_i[x][y])/(M*N);
        }
    }
    imwrite("lpf_idft_shift.bmp",LPF_idft_shift);
    imwrite("butter_idft_shift.bmp",Butter_idft_shift);
    imwrite("gussian_idft_shift.bmp",Gussian_idft_shift);
    
    return 0;
    
}