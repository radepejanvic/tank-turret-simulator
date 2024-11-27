
#include "voltmeter.h"
#include "stb_image.h"

const char* Voltmeter::VERT_SHADER = "voltmeter.vert";
const char* Voltmeter::FRAG_SHADER = "voltmeter.frag";
const char* Voltmeter::TEXTURE = "Voltmeter.png";

Voltmeter::Voltmeter(float maxV, float step, float x, float y, float a): maxV(maxV), step(step), x(x), y(y), a(a), isOn(false), currV(0), shader(VERT_SHADER, FRAG_SHADER)
{
	float base[] = {
		x - a/2, y + a/2, 1.0,    0.0, 1.0,
		x + a/2, y + a/2, 1.0,    1.0, 1.0,
		x + a/2, y - a/2, 1.0,    1.0, 0.0,
		x - a/2, y - a/2, 1.0,    0.0, 0.0
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	glGenVertexArrays(1, &bVAO);
	glBindVertexArray(bVAO);

	glGenBuffers(1, &bVBO);
	glBindBuffer(GL_ARRAY_BUFFER, bVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(base), base, GL_STATIC_DRAW);

	glGenBuffers(1, &bEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	
	int width, height, nrChannels;
	unsigned char* data = stbi_load(TEXTURE, &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR::FAILED TO LOAD TEXTURE" << std::endl;
	}
	stbi_image_free(data);

	float line[] = {
		x, y, 1.0,
		x - 0.8 * a/2, y, 1.0
	};

	glGenVertexArrays(1, &lVAO);
	glBindVertexArray(lVAO);

	glGenBuffers(1, &lVBO);
	glBindBuffer(GL_ARRAY_BUFFER, lVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Voltmeter::toggle()
{
	isOn = !isOn;
	if (!isOn) {
		currV = 0;
	}
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
	return currV / maxV;
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
	shader.setMat3("transform", generateRotationMat3(x, y, angle));
	glLineWidth(5.0f);
	glDrawArrays(GL_LINES, 0, 2);

	glUseProgram(0);
}
