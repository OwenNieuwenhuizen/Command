// ======================================================================
// \title  PiCam.cpp
// \brief  Component for recording with PiCam placeholder. Use fprime-util impl
// ======================================================================

#include "Components/PiCam/PiCam.hpp"
#include "FpConfig.hpp"
#include "fprime/Fw/Types/CommonTypes.hpp"  // Hypothetical include for the response status types
#include "fprime/Fw/Cmd/CmdPacket.hpp"  // Assuming CmdResponse might be defined here
#include <Picamera2Wrapper.hpp>  // Include the wrapper for PiCamera2

namespace Components {

    PiCam :: PiCam(const char* const compName) :
        ActiveComponentBase(compName) {
        this->camera.setup(); // Setup the camera using the wrapper
    }

    PiCam :: ~PiCam() {
        // Clean up resources if needed
    }

    // Method to handle sending of command responses
    void PiCam::cmdResponse_out(FwOpcodeType opCode, U32 cmdSeq, Fw::CmdResponse response) {
        // Log the response
        char logMsg[100];
        snprintf(logMsg, sizeof(logMsg), "Command response for opcode %d: %d", opCode, response);
        this->log_ACTIVITY_HI(logMsg);

        // Assuming there's a method in the base class to send responses
        // If no such method exists, you might need to trigger an event or update a status directly
        this->commandComplete(opCode, cmdSeq, response);
    }

    void PiCam ::
    StartRecording_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq,
        const Fw::EightyCharString& output_path,
        Quality quality
    )
    {
        auto cmdResp = Fw::CmdResponse::OK;  // Use the custom enum

        try {
            this->camera.startRecording(output_path.toChar(), quality);
            this->tlmWrite_RecordingState(true);
        } catch (const std::exception& e) {
            this->log_ERROR_HI_CameraEvent("Failed to start recording: " + Fw::EightyCharString(e.what()));
            cmdResp = Fw::CmdResponse::EXECUTION_ERROR;
        }

        this->cmdResponse_out(opCode, cmdSeq, cmdResp);  // Adjust method name as per actual implementation
    }

    void PiCam ::
    StopRecording_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
    {
        auto cmdResp = Fw::CmdResponse::OK;  // Use the custom enum

        try {
            this->camera.stopRecording();
            this->tlmWrite_RecordingState(false);
        } catch (const std::exception& e) {
            this->log_ERROR_HI_CameraEvent("Failed to stop recording: " + Fw::EightyCharString(e.what()));
            cmdResp = Fw::CmdResponse::EXECUTION_ERROR;
        }

        this->cmdResponse_out(opCode, cmdSeq, cmdResp);
    }

}