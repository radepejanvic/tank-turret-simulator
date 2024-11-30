#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D aTexture;
uniform bool isOn;
uniform float dimFactor;     

void main()
{ 
    vec4 texColor = texture(aTexture, TexCoord);
    
    if (!isOn)
        texColor = mix(texColor, vec4(0.0, 0.0, 0.0, texColor.a), dimFactor);

    if (texColor.a < 0.1)
        discard;
    
    FragColor = texColor;
}
