#include "CameraProvider.hpp"

CameraProvider::CameraProvider(int deviceID) {
    cap.open(deviceID);
}

CameraProvider::~CameraProvider() {
    cap.release();
}

bool CameraProvider::isOpened() const {
    return cap.isOpened();
}

bool CameraProvider::getFrame(cv::Mat& frame) {
    return cap.read(frame);
}