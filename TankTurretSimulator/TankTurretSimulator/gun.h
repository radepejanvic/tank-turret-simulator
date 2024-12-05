#ifndef GUN_H
#define GUN_H

#include "utils.h"
#include "shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <mutex>
#include <cmath>

class Gun {
public:
	Gun(float x, float y, float w, float h);
	void draw();

	static const char* VERT_SHADER;
	static const char* FRAG_SHADER;
	static const char* TEXTURE;
private:
	unsigned int VAO, texture;
	Shader shader;
};

#endif // !GUN_H

