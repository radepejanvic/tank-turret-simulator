#ifndef LED_H
#define LED_H

#include "utils.h"
#include "shader.h"
#include <GL/glew.h>
#include <string>

class LED {
public: 
	LED(float x, float y, float radius, int segments);
	void Toggle();
	void Draw();

	static const char* VERT_SHADER;
	static const char* FRAG_SHADER;
private: 
	bool isOn;
	float x, y, radius, segments;
	unsigned int VAO, VBO;
	Shader shader;
};

#endif // !LED_H
