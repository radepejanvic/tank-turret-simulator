#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 chCol; 

uniform sampler2D aTexture;

out vec4 outCol; 

void main()
{
    FragColor = texture(aTexture, TexCoord);
    outCol = chCol;
}
