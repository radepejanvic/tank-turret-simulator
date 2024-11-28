#include "utils.h"
#include <iostream>

std::vector<float> generateCircleVertices(float centerX, float centerY, float radius, int segments)
{
    std::vector<float> vertices;

    for (int i = 0; i < segments; ++i) {
        float angle = (2.0f * M_PI * i) / segments;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        vertices.push_back(x);
        vertices.push_back(y);
    }
    
    return vertices;
}

unsigned int generateTexturedSquare(float x, float y, float a)
{
	float base[] = {
		x - a / 2, y + a / 2, 1.0,    0.0, 1.0,
		x + a / 2, y + a / 2, 1.0,    1.0, 1.0,
		x + a / 2, y - a / 2, 1.0,    1.0, 0.0,
		x - a / 2, y - a / 2, 1.0,    0.0, 0.0
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(base), base, GL_STATIC_DRAW);

	unsigned int EBO; 
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return VAO; 
}

unsigned int generateTexturedRect(float x, float y, float w, float h)
{
	float base[] = {
		x - w / 2, y + h / 2, 1.0,    0.0, 1.0,
		x + w / 2, y + h / 2, 1.0,    1.0, 1.0,
		x + w / 2, y - h / 2, 1.0,    1.0, 0.0,
		x - w / 2, y - h / 2, 1.0,    0.0, 0.0
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(base), base, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return VAO;
}

unsigned int generateLine(float x1, float y1, float x2, float y2)
{
	float line[] = {
		x1, y1, 1.0,
		x2, y2, 1.0
	};

	unsigned int VAO; 
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO; 
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return VAO; 
}

glm::mat3 generateRotationMat3(float x, float y, float angle)
{
    float cosA = glm::cos(angle);
    float sinA = glm::sin(angle);

    glm::mat3 transform = glm::mat3(
        cosA,                    sinA,                    0,  // First column
        -sinA,                   cosA,                    0,  // Second column
        x - x * cosA + y * sinA, y - x * sinA - y * cosA, 1   // Third column
    );

    return transform;
}

glm::mat3 generateTranslationMat3Y(float deltaY)
{
    glm::mat3 transform = glm::mat3(
        1, 0, 0,  
        0, 1, 0,  
        0, deltaY, 1   
    );

    return transform;
}

unsigned int loadTexture(const char* path)
{
	unsigned int texture; 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
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
    
	return texture;
}
