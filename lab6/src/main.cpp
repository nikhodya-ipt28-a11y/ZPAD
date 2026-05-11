#include "CameraProvider.hpp"
#include "Display.hpp"
#include "FrameProcessor.hpp"
#include "KeyProcessor.hpp"

int main() {
    CameraProvider camera(0);
    if (!camera.isOpened()) {
        return -1;
    }

    Display display("LAB6 Camera");
    FrameProcessor processor;
    KeyProcessor inputHandler;

    cv::Mat frame;
    while (true) {
        if (!camera.getFrame(frame)) break;

        processor.process(frame);
        display.show(frame);

        int key = cv::waitKey(30);
        if (!inputHandler.handleKey(key, processor)) break;
    }

    return 0;
}