#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ShaderReader/ShaderReader.h"
#include "ShaderInterface/ShaderInterface.h"
#include "math.h"
#include <chrono>

typedef std::chrono::time_point<std::chrono::system_clock> test_clock;

class Testing : public ShaderInterface
{
    // Interface level functions/variables
public:
	Testing();
	unsigned int get_vao() override;
	unsigned int get_shader_program() override;
    void render() override;
private:
	unsigned int setup_vao() override;
	unsigned int setup_shader_program() override;

	// Implementation Level Functions
public:
    void set_time_since_start(double time_since_start);
    double get_time_since_start();
private:

    // Implementation level variables
public:
private:
	double time_since_start;
    test_clock start_time;
};
