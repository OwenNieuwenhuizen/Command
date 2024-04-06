module Components {
    @ Gimbal Software
    active component Gimbal {

        @ Async command to set position of servo 1
        async command SET_SERVO1_POSITION(
            position: U8 @< Desired position of servo 1 (0 to 180)
        )

        @ Async command to set position of servo 2
        async command SET_SERVO2_POSITION(
            position: U8 @< Desired position of servo 2 (0 to 180)
        )

        @ Indicates an invalid argument was received for setting servo position 1.
        event InvalidServo1Argument(badArgument: U8) \
            severity warning low \
            format "Invalid argument received for setting servo position 1: {}"

        @ Indicates an invalid argument was received for setting servo position 2.
        event InvalidServo2Argument(badArgument: U8) \
            severity warning low \
            format "Invalid argument received for setting servo position 2: {}"

        @ Reports the state we set for servo 1 position.
        event SetServo1Position(position: U8) \
            severity activity high \
            format "Set servo 1 position to {}."

        @ Reports the state we set for servo 2 position.
        event SetServo2Position(position: U8) \
            severity activity high \
            format "Set servo 2 position to {}."

        @ Telemetry channel to report position for servo 1.
        telemetry Servo1Position: U8

        @ Telemetry channel to report position for servo 2.
        telemetry Servo2Position: U8

        @ Port receiving calls from the rate group
        sync input port run: Svc.Sched

        @ Port sending calls to the GPIO driver
        output port gpioSet: Drv.GpioWrite
        ##############################################################################
        #### Uncomment the following examples to start customizing your component ####
        ##############################################################################

        # @ Example async command
        # async command COMMAND_NAME(param_name: U32)

        # @ Example telemetry counter
        # telemetry ExampleCounter: U64

        # @ Example event
        # event ExampleStateEvent(example_state: Fw.On) severity activity high id 0 format "State set to {}"

        # @ Example port: receiving calls from the rate group
        # sync input port run: Svc.Sched

        # @ Example parameter
        # param PARAMETER_NAME: U32

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Port for sending command registrations
        command reg port cmdRegOut

        @ Port for receiving commands
        command recv port cmdIn

        @ Port for sending command responses
        command resp port cmdResponseOut

        @ Port for sending textual representation of events
        text event port logTextOut

        @ Port for sending events to downlink
        event port logOut

        @ Port for sending telemetry channels to downlink
        telemetry port tlmOut

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

    }
}
