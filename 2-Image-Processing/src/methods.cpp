#include <opencv2/opencv.hpp>
#include <iostream>

#include "methods.hpp"

using namespace std;
using namespace cv;

Mat insert_watermark(Mat initial_image, Mat watermark, double input)
{
    double alpha = 0.5; double beta;
    Mat watermarked_image;

    if (input >= 0 && input <= 1) alpha = input;

    beta = ( 1.0 - alpha );
    addWeighted(initial_image, alpha, watermark, beta, 0.0, watermarked_image);

    return watermarked_image;
}