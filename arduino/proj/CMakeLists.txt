set(ARDUINO_DEFAULT_BOARD uno)
set(ARDUINO_DEFAULT_PORT com5)

set(
	proj_SRCS
	
	sys/TimerOne.cpp
	sys/MsTimer2.cpp
	sys/utilities.cpp
	
	time/DeltaObject.cpp
	time/DeadLineObject.cpp
	time/TransitionalValue.cpp
	
	out/MotorControl.cpp
	out/MotorMovementControl.cpp

	bus/string_constants.cpp
	bus/Parser.cpp
	bus/Function.cpp
	bus/Register.cpp
	bus/SerialCommunication.cpp
	
	out/Motors.cpp
	
	program.cpp
)

generate_arduino_firmware(proj)
