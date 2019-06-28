#include "Init\Window.h"
#include <Utils\String.h>
#include <Utils\Static\CInOut.h>
#include <Utils\Maths\maths.h>
#include <Utils\Fileutils.h>
#include "Rendering\Shader\Shader.h"
#include "Managers\Control_Manager.h"
#include "Rendering\Renderer\Buffers\Buffers.h"

using namespace Utils;
using namespace Core::Init;
using namespace Core::Manager;
using namespace Core::Rendering;

int main() {

	Window window("Test", 800, 600);
	//glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	Control_Manager* C_Manager = new Control_Manager();
	window.setControl(C_Manager);

	#if 0
	GLfloat vertices[] = {
		4.0,	3.0f,	0.0f,
		12.0f,	3.0f,	0.0f,
		4.0f,	6.0f,	0.0f,
		4.0f,	6.0f,	0.0f,
		12.0f,	6.0f,	0.0f,
		12.0f,	3.0f,	0.0f
	};

	GLuint vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	#else
	GLfloat vertices[] = {
		0,	0,	0,
		0,	3,	0,
		8,	3,	0,
		8,	0,	0

	};

	GLuint indicies[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLfloat colors[] = {
		1, 1, 0, 1,
		0, 1, 1, 1,
		1, 0, 1, 1,
		0, 1, 1, 1
	};

	VertexArray vao;
	Buffer* vbo = new Buffer(vertices, 4 * 3, 3);
	IndexBuffer ibo(indicies, 6);

	// VertexShader Location = 0 so 0 as index
	vao.addBuffer(vbo, 0);
	vao.addBuffer(new Buffer(colors, 4 * 4, 4), 1);

#endif

	Shader shader("Assets/Shaders/vertex_shader_test.glsl", "Assets/Shaders/fragment_shader_test.glsl");
	shader.enable();

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4,3,0)));
	shader.setUniform4f("color", vec4(0.0f, 0.3f, 0.8f, 1.0f));
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	while (!window.closed()) {
		window.clear();
		double x, y;
		C_Manager->getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float) (x * 16.0f / 960.0f),(float) (9.0f - y * 9.0f / 540.0f )));
#if 0
		glDrawArrays(GL_TRIANGLES, 0, 6);
#else
		vao.bind();
		ibo.bind();
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, 0);
		ibo.unbind();
		vao.unbind();		
#endif
		window.update();
	}

	return 0;
}