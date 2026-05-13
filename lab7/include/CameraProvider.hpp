#pragma once
#include <opencv2/opencv.hpp>

class CameraProvider {
public:
    CameraProvider(int deviceID = 0);
    ~CameraProvider();
    bool isOpened() const;
    bool getFrame(cv::Mat& frame);
private:
    cv::VideoCapture cap;
};