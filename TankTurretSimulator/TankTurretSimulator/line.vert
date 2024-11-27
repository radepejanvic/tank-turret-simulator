#version 330 core 

layout(location = 0) in vec2 inPos; 
out vec4 chCol;

uniform bool isOn;

void main() 
{
	gl_Position = vec4(inPos, 0.0, 1.0); 
	if (isOn) {
		chCol = vec4(1.0, 0.0, 0.0, 1.0);
	} else {
		chCol = vec4(0.541, 0.0, 0.0, 1.0);
	}
}