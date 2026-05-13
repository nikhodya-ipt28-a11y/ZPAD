#include "FaceDetector.hpp"

FaceDetector::FaceDetector(std::string protoPath, std::string modelPath) {
    net = cv::dnn::readNetFromCaffe(protoPath, modelPath);
}

FaceDetector::~FaceDetector() { stop(); }

void FaceDetector::start() {
    running = true;
    worker = std::thread(&FaceDetector::workerLoop, this);
}

void FaceDetector::stop() {
    running = false;
    if (worker.joinable()) worker.join();
}

void FaceDetector::updateFrame(const cv::Mat& frame) {
    std::lock_guard<std::mutex> lock(mtxIn);
    frame.copyTo(currentFrame);
    frameReady = true;
}

std::vector<cv::Rect> FaceDetector::getDetectedFaces() {
    std::lock_guard<std::mutex> lock(mtxOut);
    return results;
}

void FaceDetector::workerLoop() {
    while (running) {
        cv::Mat input;
        {
            if (!frameReady) {
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
                continue;
            }
            std::lock_guard<std::mutex> lock(mtxIn);
            input = currentFrame.clone();
            frameReady = false;
        }

        if (input.empty()) continue;

        
        cv::Mat blob = cv::dnn::blobFromImage(input, 1.0, cv::Size(300, 300), cv::Scalar(104, 177, 123));
        net.setInput(blob);
        cv::Mat detections = net.forward();

        std::vector<cv::Rect> detected;
        float* data = (float*)detections.data;

        for (int i = 0; i < detections.size[2]; i++) {
            float confidence = data[i * 7 + 2];
            if (confidence > 0.5) {
                int x1 = static_cast<int>(data[i * 7 + 3] * input.cols);
                int y1 = static_cast<int>(data[i * 7 + 4] * input.rows);
                int x2 = static_cast<int>(data[i * 7 + 5] * input.cols);
                int y2 = static_cast<int>(data[i * 7 + 6] * input.rows);
                detected.push_back(cv::Rect(cv::Point(x1, y1), cv::Point(x2, y2)));
            }
        }

        {
            std::lock_guard<std::mutex> lock(mtxOut);
            results = detected;
        }
    }
}