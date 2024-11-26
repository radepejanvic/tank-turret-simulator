#include "led.h"

const char* LED::VERT_SHADER = "led.vert";
const char* LED::FRAG_SHADER = "led.frag";

LED::LED(float x, float y, float radius, int segments) : x(x), y(y), radius(radius), segments(segments), isOn(false), shader(VERT_SHADER, FRAG_SHADER)
{
    std::vector<float> vertices = generateCircleVertices(x, y, radius, segments);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void LED::Toggle()
{
	isOn = !isOn;
}

void LED::Draw()
{
    shader.use();
    glBindVertexArray(VAO);
    
    glDrawArrays(GL_TRIANGLE_FAN, 0, segments);
    shader.setBool("isOn", isOn);

    glUseProgram(0);
}

