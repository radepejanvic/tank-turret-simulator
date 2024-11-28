#include "ammo.h"

const char* Ammo::VERT_SHADER = "ammo.vert";
const char* Ammo::FRAG_SHADER = "ammo.frag";
const char* Ammo::TEXTURE = "Bullet.png";

Ammo::Ammo(float maxA, float x, float y, float w, float h, float margin) : maxA(maxA), currA(maxA), x(x), y(y), w(w), h(h), margin(margin), shader(VERT_SHADER, FRAG_SHADER)
{
	unit_h = (h - 9 * margin) / 10;

	float base[] = {
		x,     y + unit_h, 1.0,    0.0, 1.0,
		x + w, y + unit_h, 1.0,    1.0, 1.0,
		x + w, y,          1.0,    1.0, 0.0,
		x,     y,          1.0,    0.0, 0.0
	}; 

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(base), base, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	texture = loadTexture(TEXTURE);
}

void Ammo::fire()
{
	std::lock_guard<std::mutex> lock(m);
	currA = currA-- < 0 ? 0 : currA--;
}

void Ammo::reload()
{
	std::lock_guard<std::mutex> lock(m);
	currA = maxA;
}

void Ammo::draw()
{
	std::lock_guard<std::mutex> lock(m);
	shader.use();
	glBindTexture(GL_TEXTURE_2D, texture);
	shader.setInt("aTexture", 0);
	glBindVertexArray(VAO);

	float deltaY = 0;
	for (int i = 0; i < currA; i++) {
		shader.setMat3("transform", generateTranslationMat3Y(deltaY));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		deltaY += margin + unit_h; 
	}

	glUseProgram(0);
}
