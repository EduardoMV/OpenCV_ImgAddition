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

int main() {
    GrayMix();
}
