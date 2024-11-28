#ifndef LED_H
#define LED_H

#include "utils.h"
#include "shader.h"
#include <GL/glew.h>
#include <string>

class LED {
public: 
	LED(float x, float y, float a);
	void toggle();
	void draw();

	static const char* VERT_SHADER;
	static const char* FRAG_SHADER;
	static const char* TEXTURE;
private: 
	bool isOn;
	float x, y, a;
	unsigned int VAO, texture;
	Shader shader;
};

#endif // !LED_H
