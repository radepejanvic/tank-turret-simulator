#include "visor.h"

const char* Visor::VERT_SHADER = "visor.vert";
const char* Visor::FRAG_SHADER = "visor.frag";
const char* Visor::TEXTURE = "Aim2.png";

Visor::Visor(float a): x(0), y(0), shader(VERT_SHADER, FRAG_SHADER)
{
	VAO = generateTexturedRect(0, 0, a, a, 0.0, 1.0, 0.5, 1.0);
	texture = loadTexture(TEXTURE);

	generateDynamicLine(&lVAO, &lVBO);
}

void Visor::draw(float speed)
{
	drawLine();
	drawCurr(speed);
	drawAim();
}

void Visor::drawAim()
{
	shader.use();
	glBindTexture(GL_TEXTURE_2D, texture);
	shader.setInt("aTexture", 0);
	shader.setBool("isAim", true);
	shader.setBool("isLine", false);
	shader.setMat3("transform", generateTranslationMat3Y(mouseX, mouseY));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	glUseProgram(0);
}

void Visor::drawCurr(float speed)
{
	calcGunOffset(speed);

	shader.use();
	glBindTexture(GL_TEXTURE_2D, texture);
	shader.setInt("aTexture", 0);
	shader.setBool("isAim", false);
	shader.setBool("isLine", false);
	shader.setMat3("transform", generateTranslationMat3Y(x, y));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glUseProgram(0);
}

void Visor::drawLine()
{
	float vertices[] = { x, y, 1.0, mouseX, mouseY, 1.0 };

	glBindBuffer(GL_ARRAY_BUFFER, lVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shader.use();
	shader.setBool("isLine", true);
	glLineWidth(1.0f); 
	glBindVertexArray(lVAO);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Visor::moveAim(float x, float y) {
	mouseX = x;
	mouseY = y;
}

float* Visor::getGunCoords()
{
	float coords[] = {x, y};
	return coords;
}

void Visor::calcGunOffset(float speed) 
{
	float d = distance(x, y, mouseX, mouseY);
	speed = speed < d ? speed : d;

	float dX = std::abs(mouseX - x);
	float dY = std::abs(mouseY - y);
	float theta = std::atan(dY / dX);
	
	float speedX = std::cos(theta) * speed;
	float speedY = std::sin(theta) * speed;

	if (x > mouseX) x -= speedX;
	else if (x < mouseX) x += speedX; 

	if (y > mouseY) y -= speedY;
	else if (y < mouseY) y += speedY;

	clampToCircle();
}

void Visor::clampToCircle() {
	float length = std::sqrt(x * x + y * y);
	if (length > 1.0f) {
		x /= length;
		y /= length;
	}
}