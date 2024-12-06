#include "interior.h"

const char* Interior::VERT_SHADER = "basic.vert";
const char* Interior::FRAG_SHADER = "basic.frag";
const char* Interior::TEXTURE = "res/interior.png";

Interior::Interior() : shader(VERT_SHADER, FRAG_SHADER)
{
	VAO = generateTexturedRect(0.0, 0.0, 2.4, 2.0, 0.0, 1.0, 1.0, 1.0);
	texture = loadTexture(TEXTURE);
}

void Interior::draw()
{
	shader.use();
	glBindTexture(GL_TEXTURE_2D, texture);
	shader.setInt("aTexture", 0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	shader.unbind();
}
