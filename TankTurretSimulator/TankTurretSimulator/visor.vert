#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
uniform mat3 transform;
uniform bool isAim;
uniform bool isLine;

void main()
{
    if (isLine) {
        gl_Position = vec4(aPos, 1.0);
    } else {
        gl_Position = vec4(transform * aPos, 1.0);
        if (isAim) {
            TexCoord = vec2(aTexCoord.x, aTexCoord.y);
        } else {
            TexCoord = vec2(aTexCoord.x + 0.5, aTexCoord.y);
        }
    }
}
