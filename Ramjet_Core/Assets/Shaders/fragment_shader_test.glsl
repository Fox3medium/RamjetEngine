#version 330

layout (location = 0) out vec4 FragColor;

uniform vec4 color;
uniform vec2 light_pos;

in vec4 pos;


void main() 
{
	float intensity = 1.0 / length(pos.xy - light_pos);
	FragColor = color * intensity;
}