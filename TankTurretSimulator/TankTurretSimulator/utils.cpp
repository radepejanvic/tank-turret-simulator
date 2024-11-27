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
