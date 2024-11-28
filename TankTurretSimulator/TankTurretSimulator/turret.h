#ifndef TURRET_H
#define TURRET_H 

#include "ammo.h"
#include "led.h"
#include"voltmeter.h"

class Turret {
public: 
	Turret();
	void fire();
	void draw();

private: 
	Ammo ammo; 
	LED led; 
	Voltmeter voltmeter; 
};

#endif // !TURRET_H
