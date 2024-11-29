#ifndef VISOR_H
#define VISOR_H

#include "utils.h"
#include "shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <mutex>

class Visor {
public:
	Visor(float x, float y, float a);
	void draw();

	static const char* VERT_SHADER;
	static const char* FRAG_SHADER;
	static const char* TEXTURE;
private:
	float x, y, a;
	unsigned int VAO, texture;
	Shader shader;
};

#endif // !VISOR_H
