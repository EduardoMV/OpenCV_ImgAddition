#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

void GrayMix(){
    Mat f = imread("../flower.jpg", IMREAD_GRAYSCALE);
    Mat g = imread("../Dog.jpg", IMREAD_GRAYSCALE);

    int srows = min(f.rows, g.rows);
    int scols = min(f.cols, g.cols);

    Mat h(srows, scols, CV_8U, Scalar(0));

    for(int row = 0; row < srows; row++){
        for(int col = 0; col < scols; col++){
            h.at<uchar>(row,col) = (uchar)(((f.at<uchar>(row,col) + g.at<uchar>(row,col))/2));
        }
    }

    namedWindow("PhotoFrame", WINDOW_NORMAL);
    imshow("PhotoFrame", h);
    imwrite("Mixed.jpg", h);
    waitKey(0);
}

void ColorMix(){
    Mat f = imread("../flower.jpg");
    Mat g = imread("../Dog.jpg");

    int srows = min(f.rows, g.rows);
    int scols = min(f.cols, g.cols);

    Mat h(srows, scols, CV_8UC3, Scalar(0, 0, 0));

    for(int row = 0; row < srows; row++){
        for(int col = 0; col < scols; col++){
            for (int channel = 0; channel < 3; channel++) {
                h.at<Vec3b>(row,col) = (Vec3b)(((f.at<Vec3b>(row,col) + g.at<Vec3b>(row,col))/2));
            }
        }
    }

    namedWindow("PhotoFrame", WINDOW_NORMAL);
    imshow("PhotoFrame", h);
    imwrite("ColorMix.jpg", h);
    waitKey(0);
}

void constantAdd(){
    Mat f = imread("../flower.jpg", IMREAD_GRAYSCALE);

    Mat h(f.rows, f.cols, CV_8U, Scalar(0));

    for(int row = 0; row < f.rows; row++){
        for(int col = 0; col < f.cols; col++){
            int color = f.at<uchar>(row, col) + 50;

            if(color > 255){
                h.at<uchar>(row,col) = (uchar)(255);
            }
            else{
                h.at<uchar>(row,col) = (uchar)(color);
            }

        }
    }

    namedWindow("PhotoFrame", WINDOW_NORMAL);
    imshow("PhotoFrame", h);
    imwrite("Addition.jpg", h);
    waitKey(0);
    imshow("PhotoFrame2", f);
    waitKey(0);
}

void Degraded(){
    Mat f = imread("../flower.jpg", IMREAD_GRAYSCALE);
    Mat Deg(500,500, CV_8U, Scalar(0));

    for(int j = 0; j < Deg.rows; j++){
        for (int i = 0; i < Deg.cols; i++){
            Deg.at<uchar>(i, j) = static_cast<uchar>(255 * (static_cast<float>(j) / Deg.rows));
        }
    }

    int srows = min(f.rows, Deg.rows);
    int scols = min(f.cols, Deg.cols);

    Mat h(srows, scols, CV_8U, Scalar(0));


    for(int row = 0; row < srows; row++){
        for(int col = 0; col < scols; col++){
            float blendingFactor = static_cast<float>(col) / scols;  // Calculate blending factor
            h.at<uchar>(row, col) = static_cast<uchar>((1.0 - blendingFactor) * f.at<uchar>(row, col) + blendingFactor * Deg.at<uchar>(row, col));
        }
    }

    namedWindow("PhotoFrame", WINDOW_NORMAL);
    imshow("PhotoFrame", h);
    imwrite("Degraded.jpg", h);
    waitKey(0);
}

void Degraded2(){
    Mat f = imread("../flower.jpg", IMREAD_GRAYSCALE);

    Mat h(f.rows, f.cols, CV_8U, Scalar(0));

    for(int row = 0; row < f.rows; row++){
        for(int col = 0; col < f.cols; col++){
            int color = f.at<uchar>(row, col) + (255 * static_cast<float>(col) / f.cols);

            if(color > 255){
                h.at<uchar>(row,col) = (uchar)(255);
            }
            else{
                h.at<uchar>(row,col) = (uchar)(color);
            }
        }
    }

    namedWindow("PhotoFrame", WINDOW_NORMAL);
    imshow("PhotoFrame", h);
    imwrite("Gradient.jpg", h);
    waitKey(0);
    imshow("PhotoFrame2", f);
    waitKey(0);
}

void DegradedMixV(){
    Mat f = imread("../Girl.png", IMREAD_GRAYSCALE);
    Mat g = imread("../Birds.png", IMREAD_GRAYSCALE);

    int srows = min(f.rows, g.rows);
    int scols = min(f.cols, g.cols);

    double Inc = 1.0/srows;
    double w1 = 0.0;
    double w2 = 1.0;

    Mat h(srows, scols, CV_8U, Scalar(0));

    for(int row = 0; row < srows; row++){
            w1 = w1 + Inc;
            w2 = w2 - Inc;
        for(int col = 0; col < scols; col++){

            h.at<uchar>(row,col) = (uchar)(((w1 * f.at<uchar>(row,col)) + (g.at<uchar>(row,col) * w2)));
        }
    }

    namedWindow("PhotoFrame", WINDOW_NORMAL);
    imshow("PhotoFrame", h);
    imwrite("DegradedMixV.jpg", h);
    waitKey(0);
}

void DegradedMixH(){
    Mat f = imread("../Girl.png", IMREAD_GRAYSCALE);
    Mat g = imread("../Birds.png", IMREAD_GRAYSCALE);

    int srows = min(f.rows, g.rows);
    int scols = min(f.cols, g.cols);

    double Inc = 1.0/scols;
    double w1;
    double w2;

    Mat h(srows, scols, CV_8U, Scalar(0));

    for(int row = 0; row < srows; row++){
        w1 = 0;
        w2 = 1;
        for(int col = 0; col < scols; col++){
            w1 = w1 + Inc;
            w2 = w2 - Inc;
            h.at<uchar>(row,col) = (uchar)(((w1 * f.at<uchar>(row,col)) + (g.at<uchar>(row,col) * w2)));
        }
    }

    namedWindow("PhotoFrame", WINDOW_NORMAL);
    imshow("PhotoFrame", h);
    imwrite("DegradedMixH.jpg", h);
    waitKey(0);
}

int main() {
    DegradedMixH();
}
