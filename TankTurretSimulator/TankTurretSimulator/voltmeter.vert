#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
out vec4 chCol;

uniform bool isLine; 
uniform mat3 transform;

void main()
{
    if (isLine) {
        gl_Position = vec4(transform * aPos, 1.0);
    } else {
        gl_Position = vec4(aPos, 1.0);
    }
    TexCoord = aTexCoord;
}
