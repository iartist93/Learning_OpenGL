#include <glad\glad.h>			// include glad before glfw as it contain the opengl headers 
#include <GLFW\glfw3.h>
#include <iostream>
#include "shader.h"

#include <glm\glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>				// convert the vector/martix classes to array pointer representation to use and pass them to opengl

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

	glViewport(0, 0, 800, 600);	// tell opengl the size of the rendering window


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

	// Counter-clockwise
	int indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};


	//------------ VAO, VBO, vertex attributes -----------//

	unsigned int VBO, VAO, EBO, texture1, texture2;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	// The VBO holding vertex and color data now
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	
	// configure the attribute pointers, how each specific vertex attribute will access the VBO's data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid *) 0);
	glEnableVertexAttribArray(0);

	// (VAttrib index | comp size | comp type | normalized | stide | pointer 2 1st comp)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void *) (3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void *)(6 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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


	// ---------------- Transformations ------------------//

	//glm::mat4 trans;		// identity matrix
	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));	// transform the identifiy to rotation matrix
	//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));							// combine the scaling and transformation
	//trans = glm::translate(trans, glm::vec3(0.5f, -0.5, 0.0f));


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
	
		float currentTime = glfwGetTime();
		float greenValue = (sin(currentTime) / 2) + 0.5f;
		programShader.setFloat4("animatedColor", 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(VAO);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// --------------- transformation -------------------//
		// NOTE :: Original data at the GPU will not change
		// we just apply transformation to to it and get a new transformed value to use
		// Those functions multiply at the right like (I * T * R)
		// Here we translate the rotation(around the origin at the center of the screen)
		// each loop the rotate() will rotate the original vertex coord not the new vertex coord after the previous translateion
		// the translate change the (TX, TY, TZ) each iteration and add them to the original (x,y,z)

		glm::mat4 trans;	// I4x4
		
		trans = glm::translate(trans, glm::vec3(0.5f, 0.0f, 0.0f) * (float) glfwGetTime());
		trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		
		programShader.setMatrix4fv("transform", glm::value_ptr(trans));		// convert the mat4 class to array pointer

		//-----------------------------------------------------//

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	// drawing call
		
		//glDrawArrays(GL_TRIANGLES, 0, 3);

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