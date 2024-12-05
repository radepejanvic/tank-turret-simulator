#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D aTexture;

void main()
{ 
    vec4 texColor = texture(aTexture, TexCoord);

    if (texColor.a < 0.1)
        discard;
    
    FragColor = texColor;
}
