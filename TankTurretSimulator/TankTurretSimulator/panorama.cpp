#include "panorama.h"

const char* Panorama::VERT_SHADER = "panorama.vert";
const char* Panorama::FRAG_SHADER = "panorama.frag";
const char* Panorama::TEXTURE = "winter.jpg";

Panorama::Panorama(float x, float y, float w, float h): x(x), y(y), w(w), h(h), offset(0), shader(VERT_SHADER, FRAG_SHADER)
{
	texture = loadTexture(TEXTURE);
	VAO = generateTexturedRect(x, y, w, h);
}

void Panorama::draw() const {
	shader.use();
	glBindTexture(GL_TEXTURE_2D, texture);
	shader.setInt("aTexture", 0);
	shader.setFloat("offset", offset);
	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glUseProgram(0);
}

void Panorama::moveLeft(float speed)
{
	offset = (offset + speed) < (w / 2 - 1) ? offset + speed : (w / 2 - 1);
}

void Panorama::moveRight(float speed)
{
	offset = (offset - speed) > -(w / 2 - 1) ? offset - speed : -(w / 2 - 1);
}

