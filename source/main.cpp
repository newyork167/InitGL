#include "main.h"

bool displayWireframeMode = false;
bool wKeyHeld = false;

namespace {
   void errorCallback(int error, const char* description) {
      fprintf(stderr, "GLFW error %d: %s\n", error, description);
   }

   GLFWwindow* initialize() {
      int glfwInitRes = glfwInit();
      if (!glfwInitRes) {
         fprintf(stderr, "Unable to initialize GLFW\n");
         return nullptr;
      }

      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	  glfwWindowHint(GLFW_REFRESH_RATE, 120);

#ifdef __APPLE__
       glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

      GLFWwindow* window = glfwCreateWindow(1280, 720, "InitGL", nullptr, nullptr);
      if (!window) {
         fprintf(stderr, "Unable to create GLFW window\n");
         glfwTerminate();
         return nullptr;
      }

      glfwMakeContextCurrent(window);

      int gladInitRes = gladLoadGL();
      if (!gladInitRes) {
         fprintf(stderr, "Unable to initialize glad\n");
         glfwDestroyWindow(window);
         glfwTerminate();
         return nullptr;
      }

      return window;
   }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	GLint id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	GLint u_mouse_dot_product = glGetUniformLocation(id, "u_mouse_dot_product");
	std::vector<int> x = {(int)xpos , 0 , 0}, y = { (int)ypos, 0, 0};
	glUniform1f(u_mouse_dot_product, std::inner_product(x.begin(), x.end(), y.begin(), 0));

	GLint u_mouse_x = glGetUniformLocation(id, "u_mouse_x");
	glUniform1f(u_mouse_x, xpos);

	GLint u_mouse_y = glGetUniformLocation(id, "u_mouse_y");
	glUniform1f(u_mouse_y, ypos);

	std::cout << "Cursor Position at (" << xpos << " : " << ypos << std::endl;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cout << "Cursor Position at (" << xpos << " : " << ypos << std::endl;
	}
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void process_keyboard_input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && !wKeyHeld)
	{
        displayWireframeMode = !displayWireframeMode;
        glPolygonMode(GL_FRONT_AND_BACK, displayWireframeMode ? GL_LINE : GL_FILL);
        wKeyHeld = true;
    }
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
	{
        wKeyHeld = false;
    }
	else if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {

    }
}

int main(int argc, char* argv[]) {
    glfwSetErrorCallback(errorCallback);

    GLFWwindow* window = initialize();
    if (!window) {
        return 0;
    }

	glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

    // Set the clear color to a nice green
    glClearColor(0.15f, 0.6f, 0.4f, 1.0f);

	// Set your ShaderInterface here
	auto shader = Testing();

    while (!glfwWindowShouldClose(window)) {
		process_keyboard_input(window);
		shader.set_time_since_start(difftime(time(0), start));

        glClear(GL_COLOR_BUFFER_BIT);

        shader.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
