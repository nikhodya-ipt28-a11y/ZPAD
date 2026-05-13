#include "KeyProcessor.hpp"
#include <iostream>

bool KeyProcessor::handleKey(int key, FrameProcessor& processor) {
    if (key == 27 || key == 'q') return false; // Вихід

    switch (key) {
        case '1': processor.setMode(ProcessMode::NORMAL); break;
        case '2': processor.setMode(ProcessMode::GRAY); break;
        case '3': processor.setMode(ProcessMode::CANNY); break;
        case '4': processor.setMode(ProcessMode::BLUR); break;
    }
    return true;
}