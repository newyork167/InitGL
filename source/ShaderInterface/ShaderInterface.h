#pragma once

class ShaderInterface
{
public:
	virtual unsigned int get_vao() = 0;
	virtual unsigned int get_shader_program() = 0;
	virtual void render() = 0;
private:
	virtual unsigned int setup_vao() = 0;
	virtual unsigned int setup_shader_program() = 0;

public:
	unsigned int vao;
	unsigned int shader_program;
};