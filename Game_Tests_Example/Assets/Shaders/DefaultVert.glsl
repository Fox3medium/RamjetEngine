#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec2 mask_uv;
layout(location = 3) in float tid;
layout(location = 4) in float mid;
layout(location = 5) in vec4 color;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

uniform mat4 mask_matrix;

out DATA
{
	vec4 position;
	vec2 uv;
	vec2 mask_uv;
	float tid;
	float mid;
	vec4 color;
} vs_out;

void main()
{
	gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
	vs_out.position = ml_matrix * position;
	vs_out.uv = uv;
	vs_out.tid = tid;
	vs_out.mid = mid;
	vs_out.color = color;
	vs_out.mask_uv = mask_uv;
};
