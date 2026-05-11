#pragma once
#include <opencv2/opencv.hpp>
#include <string>

class Display {
public:
    Display(std::string winName = "Video Stream");
    void show(const cv::Mat& frame);
    static void onMouse(int event, int x, int y, int flags, void* userdata);
private:
    std::string windowName;
};