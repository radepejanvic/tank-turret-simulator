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
#include <cmath>

std::vector<float> generateCircleVertices(float centerX, float centerY, float radius, int segments);
unsigned int generateTexturedSquare(float x, float y, float a);
unsigned int generateTexturedRect(float x, float y, float w, float h);
unsigned int generateLine(float x1, float y1, float x2, float y2);
glm::mat3 generateRotationMat3(float x, float y, float angle);
glm::mat3 generateTranslationMat3Y(float x, float y);
unsigned int loadTexture(const char* path);
float distance(float x1, float y1, float x2, float y2);

#endif // !UTILS_H
