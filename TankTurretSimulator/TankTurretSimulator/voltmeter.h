#ifndef VOLTMETER_H
#define VOLTMETER_H

#include "utils.h"
#include "shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>

class Voltmeter {
public:
	Voltmeter(float maxV, float step, float x, float y, float a);
	void increase();
	void decrease();
	float getRatio() const;
	bool isOn();
	void draw() const;

	static const char* VERT_SHADER;
	static const char* FRAG_SHADER;
	static const char* TEXTURE;
private:
	float maxV, currV, step;
	float x, y, a;
	unsigned int lVAO, bVAO, texture;
	Shader shader;

	void drawBase() const;
	void drawLine() const;
};

#endif // !VOLTMETER_H
