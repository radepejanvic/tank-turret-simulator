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
