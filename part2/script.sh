#!/bin/bash

g++ -std=c++17 face_detect.cpp -o face_detect `pkg-config --cflags --libs opencv4`

if [ $? -eq 0 ]; then
    echo "Executing..."
    ./face_detect
else
    echo "Compilation failed."
fi