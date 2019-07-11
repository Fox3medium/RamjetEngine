#version 330 core

layout(location = 0) out vec4 color;

in DATA
{
	vec4 position;
	vec3 normal;
	vec2 uv;
	vec3 color;
} fs_in;

uniform vec4 u_Color;

void main()
{
	vec3 n = fs_in.normal / 2.0 + 0.5;
	color = vec4(fs_in.color, 1.0);
};