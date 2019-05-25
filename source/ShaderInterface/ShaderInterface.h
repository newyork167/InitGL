#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ShaderInterface
{
public:
	virtual GLint get_vao() = 0;
	virtual GLint get_shader_program() = 0;
	virtual void render() = 0;
private:
	virtual GLint setup_vao() = 0;
	virtual GLint setup_shader_program() = 0;

public:
	GLint vao;
	GLint shader_program;
};