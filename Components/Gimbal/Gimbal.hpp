// ======================================================================
// \title  Gimbal.hpp
// \author root
// \brief  hpp file for Gimbal component implementation class
// ======================================================================

#ifndef Components_Gimbal_HPP
#define Components_Gimbal_HPP

#include "Components/Gimbal/GimbalComponentAc.hpp"
#include <Os/Mutex.hpp>

namespace Components {

  class Gimbal :
    public GimbalComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct Gimbal object
      Gimbal(
          const char* const compName //!< The component name
      );

      //! Destroy Gimbal object
      ~Gimbal();

    PRIVATE:
      Os::Mutex lock;
      U8 servo1Position;
      bool servo1Moving;
      U8 servo2Position;
      bool servo2Moving;
      // ----------------------------------------------------------------------
      // Handler implementations for commands
      // ----------------------------------------------------------------------

      //! Handler implementation for command SET_SERVO1_POSITION
      //!
      //! Async command to set position of servo 1
      void SET_SERVO1_POSITION_cmdHandler(
          FwOpcodeType opCode, //!< The opcode
          U32 cmdSeq, //!< The command sequence number
          U8 position //!< Desired position of servo 1 (0 to 180)
      ) override;

      //! Handler implementation for command SET_SERVO2_POSITION
      //!
      //! Async command to set position of servo 2
      void SET_SERVO2_POSITION_cmdHandler(
          FwOpcodeType opCode, //!< The opcode
          U32 cmdSeq, //!< The command sequence number
          U8 position //!< Desired position of servo 2 (0 to 180)
      ) override;

  };

}

#endif
