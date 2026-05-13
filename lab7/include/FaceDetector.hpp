#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>

class FaceDetector {
public:
    FaceDetector(std::string protoPath, std::string modelPath);
    ~FaceDetector();

    void start(); 
    void stop();  
    void updateFrame(const cv::Mat& frame);
    std::vector<cv::Rect> getDetectedFaces();

private:
    void workerLoop();

    cv::dnn::Net net;
    std::thread worker;
    std::atomic<bool> running{false};
    std::atomic<bool> frameReady{false};

    std::mutex mtxIn;
    std::mutex mtxOut;

    cv::Mat currentFrame;
    std::vector<cv::Rect> results;
};