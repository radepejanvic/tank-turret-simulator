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
