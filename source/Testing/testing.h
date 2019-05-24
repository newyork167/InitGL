#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ShaderReader/ShaderReader.h"
#include "ShaderInterface/ShaderInterface.h"

class Testing : public ShaderInterface
{
public:
	Testing();
	GLint get_vao();
	GLint get_shader_program();
	void set_time_since_start(double time_since_start);
	double get_time_since_start();
private:
	GLint setup_vao();
	GLint setup_shader_program();

public:
private:
	double time_since_start;
};
