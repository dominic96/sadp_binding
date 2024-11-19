cmake_minimum_required(VERSION 3.4...3.18)
project(WebcamStreamer)

# Find Python and Pybind11
add_subdirectory(pybind11)

# Find OpenCV
#find_package(OpenCV REQUIRED)
#add_subdirectory(opencv)

# Find OpenCV
#find_package(OpenCV REQUIRED)

# Add OpenCV's installation directory
set(OpenCV_DIR "C:/Users/domin/Workspace/opencv/opencv/build")

# Specify SADP include and library directories
set(SADP_INCLUDE_DIR "C:/Users/domin/Workspace/CPP/sadp_binding/HCSadpSDKV4.4.0.25/include")
set(SADP_LIBRARY "C:/Users/domin/Workspace/CPP/sadp_binding/HCSadpSDKV4.4.0.25/lib/win64/Sadp.lib")  # Adjust extension as needed
# Or add OpenCV to the prefix path
#set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:/Users/domin/Workspace/opencv/opencv/build")

# Include directories
include_directories(${pybind11_INCLUDE_DIRS} "C:/Users/domin/Workspace/opencv/opencv/build/include" "C:/Users/domin/Workspace/CPP/sadp_binding/HCSadpSDKV4.4.0.25/include")
# Include directories
link_directories("C:/Users/domin/Workspace/opencv/opencv/build/x64/vc16/lib" "C:/Users/domin/Workspace/CPP/sadp_binding/HCSadpSDKV4.4.0.25/include")



# Add the source files
set(SOURCE_FILES
    WebcamStreamer.cpp
    binder.cpp
)

# Create the Python module
pybind11_add_module(webcam_streamer ${SOURCE_FILES})

# Link libraries
#target_link_libraries(webcam_streamer PRIVATE ${OpenCV_LIBS})
target_link_libraries(webcam_streamer PRIVATE opencv_world490 ${SADP_LIBRARY})  # Adjust version if necessary



# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(webcam_streamer
                           PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})