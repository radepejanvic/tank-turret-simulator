#include "visor.h"

const char* Visor::VERT_SHADER = "visor.vert";
const char* Visor::FRAG_SHADER = "visor.frag";
const char* Visor::TEXTURE = "hills.jpg";

Visor::Visor(float x, float y, float a): x(x), y(y), a(a), shader(VERT_SHADER, FRAG_SHADER)
{
	VAO = generateTexturedSquare(x, y, a);
	texture = loadTexture(TEXTURE);
}

void Visor::draw()
{
	//std::lock_guard<std::mutex> lock(m);
	shader.use();
	glBindTexture(GL_TEXTURE_2D, texture);
	shader.setInt("aTexture", 0);
	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glUseProgram(0);
}