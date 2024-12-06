#include "led.h"

const char* LED::VERT_SHADER = "basic.vert";
const char* LED::FRAG_SHADER = "led.frag";
const char* LED::TEXTURE = "res/Led.png";

LED::LED(float x, float y, float a) : x(x), y(y), a(a), isOn(true), shader(VERT_SHADER, FRAG_SHADER)
{
    VAO = generateTexturedRect(x, y, a, a, 0.0, 1.0, 1.0, 1.0);
	texture = loadTexture(TEXTURE);
}

void LED::toggle()
{
	std::lock_guard<std::mutex> lock(m);
	isOn = !isOn;
}

void LED::draw()
{
	std::lock_guard<std::mutex> lock(m);

	shader.use();
	glBindTexture(GL_TEXTURE_2D, texture);
	shader.setInt("aTexture", 0);
	glBindVertexArray(VAO);

	shader.setBool("isOn", isOn);
	shader.setFloat("dimFactor", 0.8);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	shader.unbind();
}

bool LED::getIsOn()
{
	std::lock_guard<std::mutex> lock(m);
	return isOn;
}

