#include <glad\glad.h>			// include glad before glfw as it contain the opengl headers 
#include <GLFW\glfw3.h>
#include <iostream>

#include <glm\glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>				// convert the vector/martix classes to array pointer representation to use and pass them to opengl

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "camera.h"
#include "objects.h"
#include "shader.h"


struct
{
	int width = 800;
	int height = 600;
} viewPort;


///GLobal Variables
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastMousePosX = viewPort.width / 2.0f;
float lastMousePosY = viewPort.height / 2.0f;
bool firstMouse = true;

Camera camera;
glm::vec3 lampPosition;


//-----------------------------------------------------------------//
// Callbacks
//------------------------------------------------------------------//
void mouse_callback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastMousePosX = xPos;
		lastMousePosY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastMousePosX;	// increase right
	float yOffset = lastMousePosY - yPos;	// increase downwards
	lastMousePosX = xPos;
	lastMousePosY = yPos;

	// objective :: update the forward vector
	camera.ProcessMouseMovement(xOffset, yOffset);
}

void mouse_scroll(GLFWwindow *window, double xOffset, double yOffset)
{
	// objective::update the FOV value
	camera.ProcessMouseScroll(xOffset, yOffset);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	// Moving the camera
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)	// Forward
		camera.ProcessKeyboardInput(FORWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)	// BackWord
		camera.ProcessKeyboardInput(BACKWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)	// Right
		camera.ProcessKeyboardInput(RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)	// Left
		camera.ProcessKeyboardInput(LEFT, deltaTime);

	// Exit the games
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}
}

//-----------------------------------------------------------------//
// Helper Functions
//-----------------------------------------------------------------//
unsigned int load_texture(GLenum texture_unit, char *file_name)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, channels_no;
	unsigned char *imageData = stbi_load(file_name, &width, &height, &channels_no, 0);

	if (imageData)
	{
		GLenum format;

		if (channels_no == 1)
			format = GL_RED;
		else if (channels_no == 3)
			format = GL_RGB;
		else if (channels_no == 4)
			format = GL_RGBA;

		glActiveTexture(texture_unit);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(imageData);
	}
	else
	{
		std::cout << "ERROR::TEXTURE::LOADING::FAILED:: " << file_name << std::endl;
	}
	return textureID;
}


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


	// ------------ callbacks & Configurations ------------//

	glfwSetWindowSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, mouse_scroll);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	// hide but capture the cursor (mouse shouldn't leave the window)

	//----------------------- Shader Programs ------------------------//

	Shader SceneCubeShader = Shader("vShader2.glsl", "fShader2.glsl");
	Shader LampShader = Shader("vShader3.glsl", "fShader3.glsl");

	//------------ VAO, VBO, vertex attributes -----------//

	unsigned int VBO, VAO, lightVAO;

	//------------------- The scene cube data ------------------//
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// The VBO holding vertex and color data now
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeNormalTexture), cubeNormalTexture, GL_STATIC_DRAW);

	// positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	// normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid *)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	// texture coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid *)(6 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);


	//------------------- The Lighting lamp data ------------------//

	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	// we already has VBO with uploaded data just bind it
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void *)NULL);
	glEnableVertexAttribArray(0);


	// Light Maps ( Diffuse + Specular )
	unsigned int diffuse_map = load_texture(GL_TEXTURE0 ,"container2.png");
	unsigned int specular_map = load_texture(GL_TEXTURE1 ,"container2_specular.png");

	SceneCubeShader.use();
	SceneCubeShader.setInt("material.diffuse", 0);	// texture unit
	SceneCubeShader.setInt("material.specular", 1);

	// ---------------- rendering options ----------------//

	// uncomment this call to draw in wireframe polygons.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	//------------------- rendering ----------------------//

	while (!glfwWindowShouldClose(window))
	{
		deltaTime = glfwGetTime() - lastFrame;
		lastFrame = glfwGetTime();

		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	// state-set function
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// state-using function

		lampPosition = glm::vec3(0.8f, 0.3f, 1.0f);

		//--------------------- Draw the Scene Cube --------------------//

		SceneCubeShader.use();

		SceneCubeShader.setFloat3("lightColor", 1.0f, 1.0f, 1.0f);
		SceneCubeShader.setFloat3("objectColor", 1.0f, 0.5f, 0.31f);
		SceneCubeShader.setFloat3("lightPos", lampPosition);
		SceneCubeShader.setFloat3("viewPos", camera.position);	
		SceneCubeShader.setFloat1("material.shininess", 16.0f);


		glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		//lightColor.x = sin(glfwGetTime() * 2.0f);
		//lightColor.y = sin(glfwGetTime() * 1.0f);
		//lightColor.z = sin(glfwGetTime() * 1.5f);

		// the properties of the light are factors of the light's colors
		glm::vec3 lightAmbient = lightColor * 0.1f;	// less impact 
		glm::vec3 lightDiffuse = lightColor * 0.8f;	// decrease the infulence
		glm::vec3 lightSpecular = glm::vec3(1.0f);	// shinny at full intensity

		SceneCubeShader.setFloat3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		SceneCubeShader.setFloat3("light.ambient", lightAmbient);
		SceneCubeShader.setFloat3("light.diffuse", lightDiffuse);
		SceneCubeShader.setFloat3("light.specular", lightSpecular);

		// Point Light
		SceneCubeShader.setFloat1("light.constant", 1.0f);
		SceneCubeShader.setFloat1("light.linear", 0.09f);
		SceneCubeShader.setFloat1("light.quadratic", 0.032f);
		SceneCubeShader.setFloat1("light.range", 13.0f);

		// Spot Light
		SceneCubeShader.setFloat3("light.position", camera.position);
		SceneCubeShader.setFloat3("light.direction", camera.forward);
		SceneCubeShader.setFloat1("light.cutoff", glm::cos(glm::radians(42.5f)));
		

		// Model matrix (from local to wolrd space)
		//glm::mat4 model;
		//model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		// View matrix (from world to camera space)
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Projection matrix (from camera to NDC)ss
		glm::mat4 projection;	// transform to the NDC using prespective projection
		projection = glm::perspective(glm::radians(camera.fov), (float)viewPort.width / (float)viewPort.height, 0.1f, 100.0f);

		//SceneCubeShader.setMatrix4fv("model", glm::value_ptr(model));
		SceneCubeShader.setMatrix4fv("view", glm::value_ptr(view));
		SceneCubeShader.setMatrix4fv("projection", glm::value_ptr(projection));

		// VAO for cubes [ render cubes ]
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 4; i++)
		{
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);

			float angel = 30.0f * i;
			model = glm::rotate(model, glm::radians(angel), glm::vec3(1.0f, 0.3f, 0.5f));

			model = glm::scale(model, glm::vec3(0.3f));

			SceneCubeShader.setMatrix4fv("model", glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		//--------------------- Draw the lamb Cube --------------------//

		LampShader.use();
		
		glm::mat4 lampModel;
		lampModel = glm::translate(lampModel, lampPosition);
		lampModel = glm::scale(lampModel, glm::vec3(0.2f));

		LampShader.setMatrix4fv("model", glm::value_ptr(lampModel));	// <-- the only difference
		LampShader.setMatrix4fv("view", glm::value_ptr(view));
		LampShader.setMatrix4fv("projection", glm::value_ptr(projection));
		LampShader.setFloat3("lightColorNow", lightColor);

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//---------------------------------------------------------------//

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