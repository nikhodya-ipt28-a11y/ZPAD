#include "FrameProcessor.hpp"

void FrameProcessor::setMode(ProcessMode mode) {
    currentMode = mode;
}

void FrameProcessor::process(cv::Mat& frame) {
    if (frame.empty()) return;

    switch (currentMode) {
        case ProcessMode::GRAY: {
            cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
            
            cv::cvtColor(frame, frame, cv::COLOR_GRAY2BGR); 
            break;
        }

        case ProcessMode::CANNY: {
            cv::Mat gray;
            
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
            
            cv::Canny(gray, frame, 10, 20);
            
            cv::cvtColor(frame, frame, cv::COLOR_GRAY2BGR);
            break;
        }

        case ProcessMode::BLUR: {
            cv::GaussianBlur(frame, frame, cv::Size(15, 15), 0);
            break;
        }

        default:
            
            break;
    }
}