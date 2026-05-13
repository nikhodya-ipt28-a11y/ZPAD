#!/bin/bash
sudo apt update
sudo apt install -y libopencv-dev cmake build-essential g++ wget

# Створюємо папку для моделей
mkdir -p models

# Завантажуємо конфігурацію та ваги мережі
echo "Завантаження моделей детекції облич..."
wget -O models/deploy.prototxt https://raw.githubusercontent.com/opencv/opencv/master/samples/dnn/face_detector/deploy.prototxt
wget -O models/res10_300x300_ssd_iter_140000.caffemodel https://github.com/opencv/opencv_3rdparty/raw/dnn_samples_face_detector_20170830/res10_300x300_ssd_iter_140000.caffemodel

echo "Готово!"