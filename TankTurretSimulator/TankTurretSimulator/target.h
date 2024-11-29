#ifndef TARGET_H
#define TARGET_H

#include "utils.h"
#include "shader.h"
#include <GL/glew.h>
#include <mutex>
#include <cstdlib>
#include <ctime>

class Target {
public:
	Target(unsigned int total, float a, float w, float h);
	void draw();
	bool isEmpty();

	void moveLeft(float speed);
	void moveRight(float speed);

	bool tryShoot(float x, float y);

	static const char* VERT_SHADER;
	static const char* FRAG_SHADER;
	static const char* TEXTURE;
private:
	unsigned int total;
	float a, w, h, offset;
	std::vector<float> offsets_x, offsets_y; 
	unsigned int VAO, texture;
	Shader shader;
	std::mutex m;
};

#endif // !TARGET_H
