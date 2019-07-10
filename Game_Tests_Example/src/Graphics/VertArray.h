#pragma once

#include <iostream>
#include <Core_OpenGL.h>

class VertArray 
{
public:
	VertArray(GLfloat* vertices, GLuint* indices, GLsizei vcount, GLsizei icount);
	VertArray(GLfloat* vertices, GLuint* indices, GLfloat* tcs, GLsizei vcount, GLsizei icount);
	VertArray(GLfloat* vertices, GLuint* indices, GLfloat* normals, GLfloat* tcs, GLsizei vcount, GLsizei icount);
	void render();

private:
	GLuint vao, ibo;
	GLsizei count;
	GLuint compile(GLfloat* vertices, GLuint* indices, GLsizei vcount, GLsizei icount);
	GLuint compile(GLfloat* vertices, GLuint* indices, GLfloat *tcs, GLsizei vcount, GLsizei icount);
	GLuint compile(GLfloat* vertices, GLuint* indices, GLfloat *normals, GLfloat *tcs, GLsizei vcount, GLsizei icount);
};