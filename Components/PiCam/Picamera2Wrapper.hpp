// ======================================================================
// \title  Picamera2Wrapper.hpp
// \brief  Wrapper Component for recording with PiCam placeholder. Use fprime-util impl
// ======================================================================

#ifndef PICAMERA2WRAPPER_HPP
#define PICAMERA2WRAPPER_HPP

#include <string>

// Assume a simple enumeration for quality levels
enum Quality {
    VERY_LOW,
    LOW,
    MEDIUM,
    HIGH,
    VERY_HIGH
};

class Picamera2Wrapper {
public:
    Picamera2Wrapper();
    ~Picamera2Wrapper();

    // Setup camera configurations
    void setup();

    // Start recording video to the specified path with the given quality
    void startRecording(const char* output_path, Quality quality);

    // Stop recording video
    void stopRecording();

private:
    // Internal state and configuration of the camera
    // This could include specific settings related to Picamera2
};

#endif // PICAMERA2WRAPPER_HPP
