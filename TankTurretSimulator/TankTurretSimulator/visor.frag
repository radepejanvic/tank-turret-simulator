#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D aTexture;
uniform bool isLine;

void main()
{ 
    if (isLine) {
        FragColor = vec4(0.545, 0.0, 0.0, 1.0);
    } else {
        vec4 texColor = texture(aTexture, TexCoord);
    
        if (texColor.a < 0.1)
            discard;
    
        FragColor = texColor;
    }
}
