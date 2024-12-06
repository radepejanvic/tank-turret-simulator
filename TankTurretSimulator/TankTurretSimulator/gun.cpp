#include "gun.h"

const char* Gun::VERT_SHADER="basic.vert";
const char* Gun::FRAG_SHADER="basic.frag";
const char* Gun::TEXTURE="res/Gun.png";

Gun::Gun(float x, float y, float w, float h): shader(VERT_SHADER, FRAG_SHADER)
{
	VAO = generateTexturedRect(x, y, w, h, 0.0, 1.0, 1.0, 1.0);
	texture = loadTexture(TEXTURE);
}

void Gun::draw()
{
	shader.use();
	glBindTexture(GL_TEXTURE_2D, texture);
	shader.setInt("aTexture", 0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	shader.unbind();
}
