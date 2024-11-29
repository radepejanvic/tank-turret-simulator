#ifndef TURRET_H
#define TURRET_H 

#include "ammo.h"
#include "led.h"
#include"voltmeter.h"
#include"panorama.h"
#include"target.h"

class Turret {
public: 
	Turret(float baseV);
	void fire(float mouseX, float mouseY);
	void draw(bool isEnterier);
	void moveRight();
	void moveLeft(); 
	void increaseV();
	void decreaseV();

private: 
	float baseV, currV; 
	Ammo ammo; 
	LED led; 
	Voltmeter voltmeter;
	Panorama panorama; 
	Target target;
};

#endif // !TURRET_H
