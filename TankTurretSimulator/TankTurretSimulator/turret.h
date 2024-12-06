#ifndef TURRET_H
#define TURRET_H 

#include "ammo.h"
#include "led.h"
#include "voltmeter.h"
#include "panorama.h"
#include "target.h"
#include "timer.h"
#include "visor.h"
#include "interior.h"
#include "text_handler.h"
#include "gun.h"
#include <GLFW/glfw3.h>
#include <locale>
#include <codecvt>
#include <vector>

class Turret {
public: 
	Turret(float baseV, const char* fontPath, const char* textPath);
	void fire(float mouseX, float mouseY);
	void draw(bool isInterior);
	void moveRight();
	void moveLeft(); 
	void increaseV();
	void decreaseV();
	bool isEnd();
	void moveAim(float mouseX, float mouseY);

	static const char* SUCCESS;
	static const char* FAIL;
	static const char* SIGNATURE;
private: 
	float baseV, currV, lastT, currT, deltaT;
	float mouseX, mouseY;
	std::vector<std::wstring> lines;
	Ammo ammo; 
	LED led; 
	Voltmeter voltmeter;
	Panorama panorama; 
	Target target;
	Timer timer;
	TextHandler textHandler;
	Visor visor;
	Gun gun;
	Interior interior;

	void loadText(const char* path);
};

#endif // !TURRET_H
