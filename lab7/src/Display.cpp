#include "Display.hpp"
#include <iostream>

Display::Display(std::string winName) : windowName(winName) {
    cv::namedWindow(windowName);
    cv::setMouseCallback(windowName, Display::onMouse, nullptr);
}

void Display::show(const cv::Mat& frame) {
    cv::imshow(windowName, frame);
}

void Display::onMouse(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        std::cout << "Mouse Click at: (" << x << ", " << y << ")" << std::endl;
    }
}