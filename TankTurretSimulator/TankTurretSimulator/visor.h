#ifndef VISOR_H
#define VISOR_H

#include "utils.h"
#include "shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <mutex>
#include <cmath>

class Visor {
public:
	Visor(float a);
	void draw(float speed);
	void moveAim(float x, float y);

	static const char* VERT_SHADER;
	static const char* FRAG_SHADER;
	static const char* TEXTURE;
private:
	float x, y;
	float mouseX, mouseY;
	unsigned int VAO, texture, lVAO, lVBO;
	Shader shader;

	void drawAim();
	void drawCurr(float speed);
	void drawLine();
	void calcGunOffset(float speed);
};

#endif // !VISOR_H
