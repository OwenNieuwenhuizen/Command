// ======================================================================
// \title  PiCam.hpp
// \brief  Component for recording with PiCam placeholder. Use fprime-util impl
// ======================================================================

#ifndef PICAM_HPP
#define PICAM_HPP

#include "fprime/Fw/Comp/ActiveComponentBase.hpp"
#include "fprime/Fw/Types/EightyCharString.hpp" // Use EightyCharString for command arguments
#include "Picamera2Wrapper.hpp"  // Include the PiCamera2 wrapper


namespace Fw {
    enum CmdResponse {
        OK,
        EXECUTION_ERROR,
        VALIDATION_ERROR
    };
}

namespace Components {

    class PiCam : public Fw::ActiveComponentBase {
    public:
        PiCam(const char* const compName);
        virtual ~PiCam();

        void cmdResponse_out(FwOpcodeType opCode, U32 cmdSeq, Fw::CmdResponse response);

        // Command handler for starting the recording
        void StartRecording_cmdHandler(
            FwOpcodeType opCode,
            U32 cmdSeq,
            const Fw::EightyCharString& output_path,
            Quality quality
        );



        // Command handler for stopping the recording
        void StopRecording_cmdHandler(
            FwOpcodeType opCode,
            U32 cmdSeq
        );

    protected:
        // Telemetry to indicate recording state
        void tlmWrite_RecordingState(bool state);

        // Logger for significant events
        void log_ERROR_HI_CameraEvent(const Fw::EightyCharString& msg);

    private:
        Picamera2Wrapper camera;  // Instance of the camera wrapper
    };

} // namespace Components

#endif // PICAM_HPP