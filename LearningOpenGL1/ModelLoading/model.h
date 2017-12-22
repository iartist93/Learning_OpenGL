#pragma once

#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>

#include "../shader.h"
//#include "../texture.h"

#include "mesh.h"

class Model
{
public:
	Model();
	Model(std::string const &path);
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
