# wobot.ai Assignment

This repository contains the solution for the video processing and face detection assignment. The project is divided into two sequential parts:

## Part 1: Frame Extraction
This section handles extracting frames from an input video and scaling them to a 640x640 resolution using GStreamer.

**How to run:**
1. Navigate to the `part1` directory.
2. Make sure the script is executable: `chmod +x script.sh`
3. Run the shell script by passing your input video as an argument:
   ```bash
   ./script.sh input1.mp4
   ```
The script will decode the video and generate a `frames` directory containing all extracted JPEG images (e.g., `frame_0000.jpg`, `frame_0001.jpg`).

---

## Part 2: Face Detection
Using OpenCV in C++, this section processes the frames extracted in Part 1. It utilizes Haar Cascades to detect faces, crops the faces from the images, and saves them into an organized output directory. Frames without any faces are automatically skipped.

**Prerequisites:**
- OpenCV 4 installed (`pkg-config` must be able to locate `opencv4`)
- A C++17 compatible compiler (`g++`)

**How to run:**
1. Navigate to the `part2` directory.
2. (Ensure that the `frames` directory extracted in Part 1 is available inside `part2`.)
3. Make sure the script is executable: `chmod +x script.sh`
4. Run the shell script to compile and execute the face detection program:
   ```bash
   ./script.sh
   ```
The program will output its progress to the console. It will create an `output/` directory containing subfolders for each frame where faces were found (e.g., `output/frame_1/face_1.jpg`).

---

## Project Structure Overview
- `part1/script.sh`: Uses `gst-launch-1.0` pipeline for video stream decoding, scaling, and JPEG encoding.
- `part2/face_detect.cpp`: The C++ source code that loads frames, applies `haarcascade_frontalface_default.xml`, crops detected faces, and saves them selectively.
- `part2/script.sh`: A helper bash script to compile the C++ source using `g++` and run the executable immediately.
