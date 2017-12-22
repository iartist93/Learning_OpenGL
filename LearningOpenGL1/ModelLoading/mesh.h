#pragma once

#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include "../shader.h"

#include <vector>
#include <sstream>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	unsigned int id;
	std::string type;
	const char *path;
};


class Mesh
{
public:
	/*  Mesh Data  */
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	/*  Functions   */
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader shader);
	
private:
	/*  Render Data  */
	unsigned int VAO, VBO, EBO;

	/*  Init the buffers */
	void SetupMesh();
};

