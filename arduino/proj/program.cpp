#include <Arduino.h>

#include "sys/MsTimer2.h"

#include "time/TransitionalValue.hpp"
#include "out/Motors.hpp"

#include "bus/SerialCommunication.hpp"

//time::TransitionalValue v(500.f, 1023.f, 1.f);
//out::MotorControl mot(10, 9);

bus::SerialCommunication s;

void interrupt()
{
	//out::mot_duty.update(1);
	if(out::mot_ctrl.available())
	{
		out::mot_ctrl.init(10000);
	}
	
	out::MotorMovementControl::pwm_t p = out::mot_ctrl.tick();
	out::mot.setDuty(p);
}

void setup()
{
	//-=Initialisation communication série=-//
	s.setup();
	//-=Fin de la section=-//
	
	//-=Initialisation timer=-//
	MsTimer2::set(1, interrupt);
	//-=Fin de la section=-//
	
	//-=Initialisation moteurs=-//
	out::mot.setup();
	//-=Fin de la section=-//
	
	//-=Démarrage interruption=-//
	MsTimer2::start();
	//-=Fin de la section=-//
}

void loop()
{
	s.update();
}