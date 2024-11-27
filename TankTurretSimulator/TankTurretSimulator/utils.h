#ifndef UTILS_H
#define UTILS_H

#define _USE_MATH_DEFINES

#include "stb_image.h"
#include <vector>
#include <math.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

std::vector<float> generateCircleVertices(float centerX, float centerY, float radius, int segments);
glm::mat3 generateRotationMat3(float x, float y, float angle);
unsigned int loadTexture(const char *path); 

#endif // !UTILS_H
