#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D aTexture;
uniform bool isLine;

void main()
{
    if (isLine) {
        FragColor = vec4(0.1843, 0.6196, 0.2667, 1.0);
    } else {
        FragColor = texture(aTexture, TexCoord);
    } 
}