#ifndef INTERIOR_H
#define INTERIOR_H

#include "utils.h"
#include "shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <mutex>
#include <cmath>

class Interior {
public:
	Interior();
	void draw();

	static const char* VERT_SHADER;
	static const char* FRAG_SHADER;
	static const char* TEXTURE;
private:
	unsigned int VAO, texture;
	Shader shader;
};

#endif // !INTERIOR_H

