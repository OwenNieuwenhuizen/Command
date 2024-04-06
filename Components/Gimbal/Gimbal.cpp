// ======================================================================
// \title  Gimbal.cpp
// \author root
// \brief  cpp file for Gimbal component implementation class
// ======================================================================

#include "Components/Gimbal/Gimbal.hpp"
#include "FpConfig.hpp"
#include <wiringPi.h> // Include WiringPi library

#define GPIO_PIN_SERVO1 18
#define GPIO_PIN_SERVO2 19
#define PWM_RANGE 1024



namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Gimbal ::
    Gimbal(const char* const compName) :
      GimbalComponentBase(compName), servo1Position(90), servo1Moving(false), servo2Position(90), servo2Moving(false)
  {
      wiringPiSetupGpio();
      pinMode(GPIO_PIN_SERVO1, PWM_OUTPUT);
      pinMode(GPIO_PIN_SERVO2, PWM_OUTPUT);
      pwmSetRange(PWM_RANGE);
  }

  Gimbal ::
    ~Gimbal()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------
  int map(int x, int in_min, int in_max, int out_min, int out_max) {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }

  void Gimbal ::
    run_handler(
        NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    this->lock.lock();
    if (this->servo1Moving) {
        int pwmValue1 = map(this->servo1Position, 0, 180, 0, PWM_RANGE);
        pwmWrite(GPIO_PIN_SERVO1, pwmValue1);
    }
    if (this->servo2Moving) {
        int pwmValue2 = map(this->servo2Position, 0, 180, 0, PWM_RANGE);
        pwmWrite(GPIO_PIN_SERVO2, pwmValue2);
    }
    this->lock.unlock();
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
       int pwmValue = map(position, 0, 180, 0, PWM_RANGE);
       pwmWrite(GPIO_PIN_SERVO1, pwmValue);
       this->lock.unlock();
       this->tlmWrite_Servo1Position(position);
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
       int pwmValue = map(position, 0, 180, 0, PWM_RANGE);
       pwmWrite(GPIO_PIN_SERVO2, pwmValue);
       this->lock.unlock();
       this->tlmWrite_Servo2Position(position);
    }
    this->cmdResponse_out(opCode, cmdSeq, cmdResp);
  }

}
