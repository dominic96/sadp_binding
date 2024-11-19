#include "WebcamStreamer.h"
#include <iostream>

#include <stdio.h>
#include <windows.h>
#include "Sadp.h"

//List of devices 
//not too happy about this 
std::vector<std::string> deviceList;

//Device information callback
void CALLBACK SadpDataCallBack(const SADP_DEVICE_INFO_V40* lpDeviceInfoV40, void* pUserData)
{
    printf("\r\n----------------------------------------\r\n");
    printf("      IP    %s\r\n", lpDeviceInfoV40->struSadpDeviceInfo.szIPv4Address); //Device IP address
    printf("     Mac    %s\r\n", lpDeviceInfoV40->struSadpDeviceInfo.szMAC);         //Device Mac address
    printf("SerialNO    %s\r\n", lpDeviceInfoV40->struSadpDeviceInfo.szSerialNO);    //Device Serial No.
    printf("  Result    %d\r\n", lpDeviceInfoV40->struSadpDeviceInfo.iResult);       //Type: 1. Device online, 2. Device update, 3. Device Offline
    printf("  byActivated    %d\r\n", lpDeviceInfoV40->struSadpDeviceInfo.byActivated);     //Type: 1. Device online, 2. Device update, 3. Device Offline
    printf("  HttP Port    %d\r\n", lpDeviceInfoV40->struSadpDeviceInfo.wHttpPort);       //Type: 1. Device online, 2. Device update, 3. Device Offline
    printf("\r\n----------------------------------------\r\n");

    std::string ip = lpDeviceInfoV40->struSadpDeviceInfo.szIPv4Address;
    std::string mac = lpDeviceInfoV40->struSadpDeviceInfo.szMAC;
    std::string sn = lpDeviceInfoV40->struSadpDeviceInfo.szSerialNO;
    int info = lpDeviceInfoV40->struSadpDeviceInfo.iResult;
    int activation = lpDeviceInfoV40->struSadpDeviceInfo.byActivated;

    //Device device(ip, mac, sn, "unknown", "Hikvision", info, activation);
    deviceList.push_back(sn);


}

WebcamStreamer::WebcamStreamer(const std::string& cameraName)
    : cameraName(cameraName), running(false) {
    // Try opening the camera
    if (std::isdigit(cameraName[0])) {
        cap.open(std::stoi(cameraName)); // Treat as index
    }
    else {
        cap.open(cameraName); // Treat as device name
    }

    if (!cap.isOpened()) {
        throw std::runtime_error("Failed to open camera: " + cameraName);
    }
}

WebcamStreamer::~WebcamStreamer() {
    stopStream();
}

void WebcamStreamer::startStream() {
    if (running.load()) return; // Already streaming
    running.store(true);
    streamThread = std::thread(&WebcamStreamer::streamLoop, this);
}

void WebcamStreamer::stopStream() {
    running.store(false);
    if (streamThread.joinable()) {
        streamThread.join();
    }
}

bool WebcamStreamer::isStreaming() const {
    return running.load();
}

std::vector<std::string> WebcamStreamer::scanDevicesOnLAN() const
{
    std::cout << "\nScanning devices...\n";


    //Enable SADP logs  3(print all logs)  "C:\\SadpLog"(log directory) false(save all log files)
    SADP_SetLogToFile(3, "C:\\SadpLog", false);
    //Enable SADP services
    int iRet = SADP_Start_V40(SadpDataCallBack);
    if (iRet == 0)
    {
        //Enabling SADP services failed. Get the error code.
        int iError = SADP_GetLastError();
        printf("SADP_Start_V40 Failed!  Err(%d)\r\n", iError);
    }
    //Set the interval for automatically searching for devices. 0-disable automatic search.
    SADP_SetAutoRequestInterval(10); //unit: second
    Sleep(20000);
    //Release SADP resources.
    SADP_Stop();

    std::cout << "\nDevices found:\n";
    for (const auto& device : deviceList) {
        //device.displayInfo();
        ;
    }

    return deviceList;
}

void WebcamStreamer::streamLoop() {
    cv::Mat frame;

    while (running.load()) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Failed to capture frame" << std::endl;
            continue;
        }

        cv::imshow("Webcam Stream", frame);
        if (cv::waitKey(1) == 27) { // Press 'ESC' to exit
            break;
        }
    }
    cap.release();
    cv::destroyAllWindows();
}

