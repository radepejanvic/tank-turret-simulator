
#include "voltmeter.h"
#include "stb_image.h"

const char* Voltmeter::VERT_SHADER = "voltmeter.vert";
const char* Voltmeter::FRAG_SHADER = "voltmeter.frag";
const char* Voltmeter::TEXTURE = "Voltmeter3.png";

Voltmeter::Voltmeter(float maxV, float step, float x, float y, float a): maxV(maxV), step(step), x(x), y(y), a(a), currV(0), shader(VERT_SHADER, FRAG_SHADER)
{
	bVAO = generateTexturedSquare(x, y, a);
	texture = loadTexture(TEXTURE);

	lVAO = generateLine(x, y, x - 0.8 * a / 2, y); 
}

bool Voltmeter::isOn() {
	return currV != 0;
}

void Voltmeter::increase()
{
	currV = (currV + step > maxV) ? maxV : currV += step;
}

void Voltmeter::decrease()
{
	currV = (currV - step < 0) ? 0 : currV -= step;
}

float Voltmeter::getRatio() const
{
	return currV == 0 ? step/maxV : currV/maxV;
}

void Voltmeter::draw() const
{
	drawBase();
	drawLine();
}

void Voltmeter::drawBase() const
{
	shader.use();
	glBindTexture(GL_TEXTURE_2D, texture);
	shader.setInt("aTexture", 0);
	glBindVertexArray(bVAO);

	shader.setBool("isLine", false);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glUseProgram(0);
}

void Voltmeter::drawLine() const
{
	float angle = -glm::radians((currV / maxV) * 180.0);

	shader.use();
	glBindVertexArray(lVAO);

	shader.setBool("isLine", true);
	if (std::rand() % 10 == 1) {
		shader.setMat3("transform", generateRotationMat3(x, y, angle + 0.03));
	}
	else {
		shader.setMat3("transform", generateRotationMat3(x, y, angle));
	}

	glLineWidth(5.0f);
	glDrawArrays(GL_LINES, 0, 2);

	glUseProgram(0);
}
