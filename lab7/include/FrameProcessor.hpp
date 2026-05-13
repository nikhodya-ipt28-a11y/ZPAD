#pragma once
#include <opencv2/opencv.hpp>

enum class ProcessMode { NORMAL, GRAY, CANNY, BLUR };

class FrameProcessor {
public:
    void setMode(ProcessMode mode);
    void process(cv::Mat& frame);
private:
    ProcessMode currentMode = ProcessMode::NORMAL;
};