// ======================================================================
// \title  Gimbal.cpp
// \author root
// \brief  cpp file for Gimbal component implementation class
// ======================================================================

#include "Components/Gimbal/Gimbal.hpp"
#include "FpConfig.hpp"

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Gimbal ::
    Gimbal(const char* const compName) :
      GimbalComponentBase(compName), servo1Position(90), servo1Moving(false), servo2Position(90), servo2Moving(false)
  {

  }

  Gimbal ::
    ~Gimbal()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void Gimbal ::
    SET_SERVO1_POSITION_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq,
        U8 position
    )
  {
    auto cmdResp = Fw::CmdResponse::OK;
    if(position > 180 || position < 0) {
       this->log_WARNING_LO_InvalidServo1Argument(position);
       cmdResp = Fw::CmdResponse::VALIDATION_ERROR;
    }
    else {
       this->lock.lock();
       this->servo1Position = position;
       this->lock.unlock();
    }
    this->cmdResponse_out(opCode, cmdSeq, cmdResp);
  }

  void Gimbal ::
    SET_SERVO2_POSITION_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq,
        U8 position
    )
  {
    auto cmdResp = Fw::CmdResponse::OK;
    if(position > 180 || position < 0) {
       this->log_WARNING_LO_InvalidServo2Argument(position);
       cmdResp = Fw::CmdResponse::VALIDATION_ERROR;
    }
    else {
       this->lock.lock();
       this->servo2Position = position;
       this->lock.unlock();
    }
    this->cmdResponse_out(opCode, cmdSeq, cmdResp);
  }

}
