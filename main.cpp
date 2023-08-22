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

int main() {
    constantAdd();
}
