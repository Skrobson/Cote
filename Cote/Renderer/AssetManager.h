#pragma once
#include <vector>
#include <map>
#include <set>
#include "Texture.h"
#include "ShaderProgram.h"
#include "Model.h"


#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
namespace cote
{
	using namespace cote::graphic;

	class AssetManager
	{
	public:
		AssetManager();
		~AssetManager();

		std::shared_ptr<Model> loadModel(const std::string& filePath, std::shared_ptr<ShaderProgram>);

	protected:

		std::vector<std::shared_ptr<Mesh>> processNode(aiNode * node, const aiScene * scene);

		std::shared_ptr<Mesh> processMesh(aiMesh * mesh, const aiScene * scene);

		std::shared_ptr<Texture> loadTexture( aiMaterial * material, aiTextureType type, std::string typeName);



		std::map<std::string, std::shared_ptr<Texture>> textures;

		//std::set<std::shared_ptr<ShaderProgram>> shaders;

		std::map<std::string, std::shared_ptr<Model>> models;

		//temporaly loading info

		std::string directory;

		std::shared_ptr<ShaderProgram> program;

	};

}


