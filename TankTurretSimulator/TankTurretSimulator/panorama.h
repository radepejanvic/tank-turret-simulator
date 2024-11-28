#ifndef PANORAMA_H
#define PANORAMA_H

#include "utils.h"
#include "shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Panorama {
public: 
	Panorama(float x, float y, float w, float h);
	void draw() const;

	void moveRight(float speed);
	void moveLeft(float speed);

	static const char* VERT_SHADER;
	static const char* FRAG_SHADER;
	static const char* TEXTURE;
private:
	float offset;
	float x, y, w, h;
	unsigned int VAO, texture;
	Shader shader;
};

#endif // !PANORAMA_H
