#include <pybind11/pybind11.h>
#include "WebcamStreamer.h"

#include <pybind11/stl.h>  // Required for STL bindings
#include <pybind11/stl_bind.h>  // Optional for advanced bindings

namespace py = pybind11;

//PYBIND11_MAKE_OPAQUE(std::vector<std::string>); // If required

PYBIND11_MODULE(webcam_streamer, m) {
    py::class_<WebcamStreamer>(m, "WebcamStreamer")
        .def(py::init<const std::string&>(), py::arg("cameraName"))
        .def("startStream", &WebcamStreamer::startStream)
        .def("stopStream", &WebcamStreamer::stopStream)
        .def("isStreaming", &WebcamStreamer::isStreaming)
        .def("scanDevices", &WebcamStreamer::scanDevicesOnLAN);
}
