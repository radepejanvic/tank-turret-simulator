#ifndef UTILS_H
#define UTILS_H

#define _USE_MATH_DEFINES

#include <vector>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

std::vector<float> generateCircleVertices(float centerX, float centerY, float radius, int segments);
glm::mat3 generateRotationMat3(float x, float y, float angle);

#endif // !UTILS_H
