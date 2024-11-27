#ifndef AMMO_H
#define AMMO_H

#include "utils.h"
#include "shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Ammo {
public:
	Ammo(float maxA, float x, float y, float w, float h, float margin);
	void fire();
	void reload();
	void draw() const;

	static const char* VERT_SHADER;
	static const char* FRAG_SHADER;
	static const char* TEXTURE;
private:
	float maxA, currA;
	float x, y, w, h, margin, unit_h;
	unsigned int VAO, VBO, EBO, texture;
	Shader shader;
};

#endif // !AMMO_H

