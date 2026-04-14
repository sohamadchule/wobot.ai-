#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>

namespace fs = std::filesystem;

int main() {
    std::string frames_dir = "frames";
    std::string output_dir = "output";
    std::string cascade_path = "haarcascade_frontalface_default.xml";

    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load(cascade_path)) {
        std::cerr << "Error loading cascade\n";
        return -1;
    }

    std::vector<fs::path> files;
    for (const auto &entry : fs::directory_iterator(frames_dir)) {
        if (entry.path().extension() == ".jpg" || entry.path().extension() == ".jpeg") {
            files.push_back(entry.path());
        }
    }

    // Sort files to ensure frames are processed sequentially
    std::sort(files.begin(), files.end());

    std::regex frame_regex("frame_(\\d+)");

    for (const auto &file_path : files) {
        cv::Mat img = cv::imread(file_path.string());
        if (img.empty()) continue;

        std::vector<cv::Rect> faces;
        cv::Mat gray;

        cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
        face_cascade.detectMultiScale(gray, faces);

        // Skip frames with NO face
        if (faces.empty()) continue;

        // Extract accurate frame number from file name (e.g. frame_0001.jpg -> 1)
        std::string filename = file_path.filename().string();
        std::smatch match;
        std::string frame_num = "unknown";
        if (std::regex_search(filename, match, frame_regex)) {
            frame_num = std::to_string(std::stoi(match[1].str()));
        }

        std::string frame_folder = output_dir + "/frame_" + frame_num;
        fs::create_directories(frame_folder);

        int face_count = 0;

        for (auto &face : faces) {
            face_count++;

            // Crop face
            cv::Mat cropped = img(face);

            std::string face_name = frame_folder + "/face_" + std::to_string(face_count) + ".jpg";
            cv::imwrite(face_name, cropped);
        }

        std::cout << "Frame " << frame_num << " ---->>> Faces: " << face_count << "\n";
    }

    return 0;
}