#include "CameraProvider.hpp"
#include "Display.hpp"
#include "FaceDetector.hpp"
#include "FrameProcessor.hpp"
#include "KeyProcessor.hpp"

int main() {
    CameraProvider camera(0);
    if (!camera.isOpened()) return -1;

    
    FaceDetector detector("models/deploy.prototxt", "models/res10_300x300_ssd_iter_140000.caffemodel");
    detector.start();

    
    FrameProcessor processor;
    KeyProcessor inputHandler;
    Display display("LAB7: AI + Filters");

    cv::Mat frame;

    while (true) {
        if (!camera.getFrame(frame)) break;

        
        detector.updateFrame(frame);

        
        processor.process(frame);

        
        auto faces = detector.getDetectedFaces();
        for (const auto& rect : faces) {
            cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 2);
            cv::putText(frame, "Face", cv::Point(rect.x, rect.y - 10), 
                        cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2);
        }

        
        display.show(frame);

        
        int key = cv::waitKey(1);
        if (key != -1) {
            if (!inputHandler.handleKey(key, processor)) break; 
        }
    }

    detector.stop();
    return 0;
}