#ifndef VOLTMETER_H
#define VOLTMETER_H

#include "utils.h"
#include "shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Voltmeter {
public:
	Voltmeter(float maxV, float step, float x, float y, float a);
	void toggle();
	void increase();
	void decrease();
	void draw();

	static const char* VERT_SHADER;
	static const char* FRAG_SHADER;
	static const char* TEXTURE;
private:
	bool isOn;
	float maxV, currV, step;
	float x, y, a;
	unsigned int lVAO, lVBO, bVAO, bVBO, bEBO, texture;
	Shader shader;

	void drawBase();
	void drawLine();

};

#endif // !VOLTMETER_H
