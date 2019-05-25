#include <Testing/testing.h>

unsigned int Testing::get_shader_program()
{
    return this->shader_program;
}

unsigned int Testing::get_vao()
{
    return this->vao;
}

double Testing::get_time_since_start()
{
    return this->time_since_start;
}

void Testing::set_time_since_start(double time_since_start)
{
    this->time_since_start = time_since_start;
}

Testing::Testing()
{
	this->shader_program = this->setup_shader_program();
	this->vao = this->setup_vao();
	this->start_time = std::chrono::system_clock::now();
}

unsigned int Testing::setup_vao()
{
    float shift = this->get_time_since_start();
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
    float vertices[] = {
            fmod(0.5f + shift, 1.0f),  fmod(0.5f + shift, 1.0f), fmod(0.0f + shift, 1.0f),  // top right
            fmod(0.5f + shift, 1.0f), fmod(-0.5f + shift, 1.0f), fmod(0.0f + shift, 1.0f),  // bottom right
            fmod(-0.5f + shift, 1.0f), fmod(-0.5f + shift, 1.0f), fmod(0.0f + shift, 1.0f),  // bottom left
            fmod(-0.5f + shift, 1.0f), fmod( 0.5f + shift, 1.0f), fmod(0.0f + shift, 1.0f)   // top left
    };
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	return VAO;
}

unsigned int Testing::setup_shader_program()
{
	const GLchar *fragmentShaderSource = ShaderReader::ReadFromFile("shaders/testing.frag");
	const GLchar *vertexShaderSource = ShaderReader::ReadFromFile("shaders/testing.vert");

	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

void Testing::render()
{
    test_clock current_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = current_time - this->start_time;
    this->set_time_since_start(elapsed_seconds.count() * 50);
    double radians = (this->get_time_since_start() * 3.1415926535897932384626433832795) / 180;
    std::cout << "Current radians: " << radians << std::endl;
    glUniform1f(glGetUniformLocation(this->get_shader_program(), "u_time"), radians);

    glUseProgram(this->get_shader_program());
    glBindVertexArray(this->get_vao());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}