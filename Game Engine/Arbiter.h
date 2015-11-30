#pragma once
#include "StrategicExpert.h"
#include "MovementExpert.h"
#include "HealthExpert.h"

class Arbiter
{
public:
	
	Arbiter();
	~Arbiter();
	StrategicExpert* stratExpert = new StrategicExpert();
	MovementExpert* moveExpert = new MovementExpert();
	HealthExpert* healExpert = new HealthExpert();
	void Update();
	

};

