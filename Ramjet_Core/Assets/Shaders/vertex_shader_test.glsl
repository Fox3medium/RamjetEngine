#version 330

layout (location = 0) in vec4 position;

// Projection matrix
uniform mat4 pr_matrix;
// View Matrix
uniform mat4 vw_matrix = mat4(1.0);
// Model Matrix		  
uniform mat4 ml_matrix = mat4(1.0);

out vec4 pos;

void main() 
{
	gl_Position = pr_matrix * vw_matrix * ml_matrix * position;

	pos = position;
}