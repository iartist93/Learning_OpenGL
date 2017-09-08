#include <glad\glad.h>			// include glad before glfw as it contain the opengl headers 
#include <GLFW\glfw3.h>
#include <iostream>
#include "shader.h"

#include <glm\glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>				// convert the vector/martix classes to array pointer representation to use and pass them to opengl

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct
{
	int width = 800;
	int height = 600;
} viewPort;

//-----------------------------------------------------------------//

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

	glViewport(0, 0, viewPort.width, viewPort.height);	// tell opengl the size of the rendering window


	// ----------------- callbacks ----------------------//

	glfwSetWindowSizeCallback(window, framebuffer_size_callback);

	// -------------- generate the vertices --------------//
	float vertices1[] = {

		//--- vertices ---         --- Colors -----
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,	    0.0f, 1.0f, 0.0f,
		0.0f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,
	};

	// Window origin is on the center
	// Texture origin is at bottom left
	float vertices2[] = {
		//   positions           // colors				// tex coords
		0.5f , 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,			// top right	
		0.5f ,-0.5f, 0.0f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,			// bottom right
		-0.5f,-0.5f, 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f,			// bottom left
		-0.5f, 0.5f, 0.0f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f			// top left
	};

	float cubeVertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	// Counter-clockwise
	int indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};
	
	// more cubes
	glm::vec3 cubePositions[] = {
		glm::vec3(-0.5f, 0.5f, 0.0f),
		glm::vec3(0.5f,  0.5f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f)
	};

	//------------ VAO, VBO, vertex attributes -----------//

	unsigned int VBO, VAO, EBO, texture1, texture2;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	// The VBO holding vertex and color data now
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	
	// configure the attribute pointers, how each specific vertex attribute will access the VBO's data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid *) 0);
	glEnableVertexAttribArray(0);

	// (VAttrib index | comp size | comp type | normalized | stide | pointer 2 1st comp)
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void *) (3 * sizeof(GL_FLOAT)));
	//glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void *)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);


	/*
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	*/

	//----------- Image loading and texture configuration --------//

	
	int width1, height1, noChannels1,
		width2, height2, noChannels2;

	stbi_set_flip_vertically_on_load(1);
	unsigned char *imageData1 = stbi_load("container.jpg", &width1, &height1, &noChannels1, 0);
	unsigned char *imageData2 = stbi_load("moana.jpg", &width2, &height2, &noChannels2, 0);
	
	// bind the buffer to the texture 2d target
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// configure the options of the bound buffer
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// loading and generating the texture and MipMap
	if (imageData1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR::TEXTURE__1__::LOADING::FAILED" << std::endl;
	}

	stbi_image_free(imageData1);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	// configure the options of the bound buffer
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if(imageData2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData2);
		
		GLenum err;
		err = glGetError();
		std::cerr << "OpenGL error: " << err << std::endl;

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR::TEXTURE__2__LOADING::FAILED" << std::endl;
	}

	stbi_image_free(imageData2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// ------------------- shader program ----------------//

	Shader programShader = Shader("vShader.glsl", "fShader.glsl");
	programShader.use();

	// set the uniform variables in the shader program
	programShader.setInt("TextureObject1", 0);
	programShader.setInt("TextureObject2", 1);

	// ---------------- rendering options ----------------//

	// uncomment this call to draw in wireframe polygons.
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	//------------------- rendering ----------------------//
	
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);	// check the current state of buttons each loop
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	// state-set function
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// state-using function
	
		/*
		float currentTime = glfwGetTime();
		float greenValue = (sin(currentTime) / 2) + 0.5f;
		programShader.setFloat4("animatedColor", 0.0f, greenValue, 0.0f, 1.0f);
		*/

		glBindVertexArray(VAO);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		//---------- Coordiation Space Transformation----------//

		//glm::mat4 view;	// transform from the wrold space to the camera space
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));	// simulate the camera move back and scene move forward

		glm::mat4 projection;	// transform to the NDC using prespective projection
		projection = glm::perspective(glm::radians(45.0f), (float)viewPort.width / (float)viewPort.height, 0.1f, 100.0f);


		// Camera coordinate space
		glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);	// move back 3 units
		
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);	// looking at the origin
		glm::vec3 cameraDirection = glm::normalize(cameraPosition - cameraDirection);	// points toword the +ve camera direcion
		
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::normalize(glm::cross(cameraDirection, up));

		glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));

		// lookat matrix
		
		//float raduis = 20.0f;
		//float camX = sin(glfwGetTime() * raduis);
		//float camY = cos(glfwGetTime() * raduis);

		glm::mat4 view;
		view = glm::lookAt(
			glm::vec3(0.0f, 4.0f, 4.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);

		/*
		for (int i = 0; i < 4; i++)
		{	
			glm::mat4 model;		// transform from the local space to the global world space
			model = glm::translate(model, cubePositions[i]);
			switch (i)
			{
			case 0:
				model = glm::rotate(model, glm::radians(50.0f) * (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
				break;
			case 1 :
				model = glm::rotate(model, glm::radians(50.0f) * (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
				break;
			case 2:
				model = glm::rotate(model, glm::radians(50.0f) * (float)glfwGetTime(), glm::vec3(0.6f, 0.3f, 0.5f));
				break;
			case 3:
				model = glm::rotate(model, glm::radians(50.0f) * (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 0.1f));
				break;
			default:
				break;
			}
			*/
			
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 0.1f));
		model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.0f, 0.1f, 0.0f));
		model = glm::scale(model, glm::vec3(0.6f));

		programShader.setMatrix4fv("model", glm::value_ptr(model));
		programShader.setMatrix4fv("view", glm::value_ptr(view));
		programShader.setMatrix4fv("projection", glm::value_ptr(projection));
			
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	// drawing call

		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cerr << "OpenGL error: " << err << std::endl;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	// delallocate all resources when we done form all
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();		// deallocate the resources 

	return 0;
}