#ifndef WEBCAMSTREAMER_H
#define WEBCAMSTREAMER_H

#include <opencv2/opencv.hpp>
#include <string>
#include <thread>
#include <atomic>
#include <vector>

class WebcamStreamer {
public:
    WebcamStreamer(const std::string& cameraName);
    ~WebcamStreamer();

    void startStream();
    void stopStream();
    bool isStreaming() const;
    std::vector<std::string> scanDevicesOnLAN() const;

private:
    void streamLoop();

    std::string cameraName;
    cv::VideoCapture cap;
    std::thread streamThread;
    std::atomic<bool> running;
};

#endif // WEBCAMSTREAMER_H

