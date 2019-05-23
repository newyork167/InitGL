#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ShaderReader/ShaderReader.h"
#include "ShaderInterface/ShaderInterface.h"

class Testing : public ShaderInterface
{
public:
	Testing();
	unsigned int get_vao();
	unsigned int get_shader_program();
	void set_time_since_start(double time_since_start);
	double get_time_since_start();
private:
	unsigned int setup_vao();
	unsigned int setup_shader_program();

public:
private:
	double time_since_start;
};
