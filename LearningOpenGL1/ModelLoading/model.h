#pragma once

#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>

#include "../shader.h"
#include "../texture.h"

#include "mesh.h"

class Model
{
public:
	Model();
	Model(std::string const &path)
	{
		LoadModel(path);
	}
	void Draw(Shader shader);

private:
	/*  Model Data   */
	std::vector<Mesh> meshes;
	std::vector<Texture> loadedTextures;
	std::string directory;		// use it later for loading texture files
	
	/*  Functions  */
	void LoadModel(std::string path);
	void ProcessNode(aiNode *node, const aiScene *scene);
	Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial *material, aiTextureType type, std::string typeName);
};

Model::Model() { }

void Model::Draw(Shader shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}

void Model::LoadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	// <-- postprocessing
	
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::cout << "ASSIMP::ERROR::IMPORTING::SCENE " << importer.GetErrorString() << std::endl;
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));		// exclude the file name and return the directory itself

	ProcessNode(scene->mRootNode, scene);	// process the root not in the scene
}

void Model::ProcessNode(aiNode *node, const aiScene *scene)
{
	// 1- Get all the meshes in the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// get the mesh
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];		// Don't node->mMeshes[i] becouse this is just the index
		
		// Process thie mesh and store it in our custome data structure
		meshes.push_back(ProcessMesh(mesh, scene));
	}

	// 2- Process all the child nodes recursivly
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures; 

	// 1- process vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		glm::vec3 position;
		position.x = mesh->mVertices[i].x;
		position.y = mesh->mVertices[i].y;
		position.z = mesh->mVertices[i].z;

		vertex.Position = position;

		glm::vec3 normal;
		normal.x = mesh->mNormals[i].x;
		normal.y = mesh->mNormals[i].y;
		normal.z = mesh->mNormals[i].z;

		vertex.Normal = normal;

		// each vertex can have up-to 8 different texture coordiates
		if (mesh->mTextureCoords[0])	// does this mesh contain any texture coordaintes?
		{
			glm::vec2 texCoords;
			texCoords.x = mesh->mTextureCoords[0][i].x;
			texCoords.y = mesh->mTextureCoords[0][i].y;
			
			vertex.TexCoords = texCoords;
		}
		else
		{
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	// process indices	
	/*    Mesh contains many faces, face contains many vertex indices (shared )   */
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}


	if (mesh->mMaterialIndex > 0)	// mesh uses only one material (return the index to the scene's material[] or -1)
	{
		// get the material itself
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		
		// pull all the diffuse textures out of it
		std::vector<Texture> diffuseTextures = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseTextures.begin(), diffuseTextures.end());	// copy vector elements to another vector 

		// pull all the specular textures out of the material
		std::vector<Texture> specularTextures = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularTextures.begin(), specularTextures.end());	// copy vector elements to another vector 
	}

	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial *material, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
	{
		bool skip = false;
		aiString path;
		material->GetTexture(type, i, &path);

		//std::cout << "Path " << path.C_Str() << std::endl;
	
		////optimization(don't load the same texture again == expensive task)
		//for (unsigned int j = 0; j < loadedTextures.size(); j++)
		//{
		//	std::cout << "Count = " << loadedTextures.size() << " ";

		//	if (loadedTextures[j].path == path.C_Str())
		//	{
		//		std::cout << "They matches " << loadedTextures[j].path << std::endl;
		//		textures.push_back(loadedTextures[j]);
		//		skip = true;
		//		break;
		//	}
		//}
		//if (!skip)
		//{
			Texture texture;
			texture.id = LoadTextureFromFile(path.C_Str(), directory);
			texture.type = typeName;
			texture.path = path.C_Str();
			textures.push_back(texture);
			
			//loadedTextures.push_back(texture);

			//std::cout << path.C_Str() << " " << directory.c_str() << std::endl;
		//}
	}
	return textures;
}



