#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
uniform mat3 transform;

void main()
{
    gl_Position = vec4(transform * aPos, 1.0);
    TexCoord = aTexCoord;
}
