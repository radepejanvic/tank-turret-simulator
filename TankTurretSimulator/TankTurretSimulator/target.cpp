#include "target.h"
const char* Target::VERT_SHADER = "target.vert";
const char* Target::FRAG_SHADER = "target.frag";
const char* Target::TEXTURE = "Target.png";

Target::Target(unsigned int total, float a, float w, float h) : total(total), a(a), w(w), h(h), shader(VERT_SHADER, FRAG_SHADER)
{
	VAO = generateTexturedSquare(0.0, 0.0, a);
	texture = loadTexture(TEXTURE);

	offset = 0.0;

	std::srand(static_cast<unsigned int>(std::time(0)));
	float x, y; 

	for (int i = 0; i < total; i++) {
		x = -(w / 2 - a) + static_cast<float>(std::rand()) / RAND_MAX * (w - 2 * a);
		y = -(h / 2 - a) + static_cast<float>(std::rand()) / RAND_MAX * (h - 2 * a);
		offsets_x.push_back(x);
		offsets_y.push_back(y);
	}
}

void Target::moveLeft(float speed)
{
	if (offset + speed <= w / 2 - 1) {
		offset += speed;
		for (size_t i = 0; i < offsets_x.size(); i++) {
			offsets_x[i] += speed;
		}
	}
}

void Target::moveRight(float speed)
{
	if (offset - speed >= -w / 2 - 1) {
		offset -= speed;
		for (size_t i = 0; i < offsets_x.size(); i++) {
			offsets_x[i] -= speed;
		}
	}
}

void Target::draw()
{
	std::lock_guard<std::mutex> lock(m);
	shader.use();
	glBindTexture(GL_TEXTURE_2D, texture);
	shader.setInt("aTexture", 0);
	glBindVertexArray(VAO);

	for (int i = 0; i < total; i++) {
		shader.setMat3("transform", generateTranslationMat3Y(offsets_x[i], offsets_y[i]));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	glUseProgram(0);
}

bool Target::isEmpty()
{
	return total == 0;
}

bool Target::tryShoot(float x, float y) 
{	
	for (int i = 0; i < total; i++) {
		if (distance(offsets_x[i], offsets_y[i], x, y) <= a/2) {
			offsets_x.erase(offsets_x.begin() + i);
			offsets_y.erase(offsets_y.begin() + i);
			total--;
			return true; 
		}
	}

	return false;
}