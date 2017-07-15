#include <glad\glad.h>			// include glad before glfw as it contain the opengl headers 
#include <GLFW\glfw3.h>
#include <iostream>
#include "shader.h"


// register a callback function on the window to be called each time the window get resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}
}

//-----------------------------------------------------------------//

int main()
{
	glfwInit();
	// set hints fot the next call of GLFWCreateWindow() call
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(800, 600, "First Window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "ERROR::Faild to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);	// tell opengl the size of the rendering window


	// ----------------- callbacks ----------------------//

	glfwSetWindowSizeCallback(window, framebuffer_size_callback);
	
	// -------------- generate the vertices --------------//
	float vertices1[] = {

		//--- vertices ---         --- Colors -----
		-0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f,	    0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f,
	};

	float vertices2[] = {
		0.5f, 0.5f, 0.0f,   // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f,	// top left
	};

	int indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	//------------ VAO, VBO, vertex attributes -----------//

	unsigned int VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	// The VBO holding vertex and color data now
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	
	// configure the attribute pointers, how this vertex attribute will access the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid *) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void *) (3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// ---------------- rendering options ----------------//

	// uncomment this call to draw in wireframe polygons.
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//------------------- rendering ----------------------//

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);	// check the current state of buttons each loop
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	// set the current color state
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// state-using function
	
		Shader programShader = Shader("vShader.glsl", "fShader.glsl");
		programShader.use();

		float currentTime = glfwGetTime();
		float greenValue = (sin(currentTime) / 2) + 0.5f;
		programShader.setFloat4("animatedColor", 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(VAO);
		
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	// drawing call
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	// delallocate all resources when we done form all
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();		// deallocate the resources 

	return 0;
}



