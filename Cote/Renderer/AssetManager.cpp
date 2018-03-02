#include "AssetManager.h"


#include <iostream>

#include <algorithm>
#include <iterator>

using namespace cote::graphic;
using namespace cote;


AssetManager::AssetManager()
{
}


AssetManager::~AssetManager()
{
}



std::shared_ptr<Model> cote::AssetManager::loadModel(const std::string & filePath, std::shared_ptr<ShaderProgram> program) //aiPostProcessSteps
{
	this->program = program;
	auto modelIterator = models.find(filePath);
	if (modelIterator == models.end())
	{
		Assimp::Importer importer;

		auto aiScene = importer.ReadFile(filePath, aiProcess_Triangulate);// | aiProcess_FlipUVs);
		if (!aiScene || aiScene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !(aiScene->mRootNode))
		{
			// exception
			std::cerr << "ERROR LOADING MODEL " << importer.GetErrorString() << std::endl;
			return nullptr;
		}

		directory = filePath.substr(0, filePath.find_last_of('/') + 1);
		auto meshes = processNode(aiScene->mRootNode, aiScene);
		
		std::cout << " End of loading, meshes: " << meshes.size() << std::endl;

		auto model = std::make_shared<Model>(meshes);
		models.insert(std::make_pair( filePath, model));
		return model;
	}
	else
		return modelIterator->second;

	
}

std::vector<std::shared_ptr<Mesh>> cote::AssetManager::processNode(aiNode * node, const aiScene * scene)
{
	std::vector<std::shared_ptr<Mesh>> meshes;

	std::cout << " meshes " << node->mNumMeshes << std::endl;
	for (size_t i = 0; i < node->mNumMeshes; ++i) 
	{

		std::cout << "nr mesh " << i << std::endl;

		size_t index = node->mMeshes[i];
		aiMesh* mesh = scene->mMeshes[index];
		meshes.push_back(processMesh(mesh, scene));
	}
	std::cout << " nodes " << node->mNumChildren << std::endl;
	for (size_t i = 0; i < node->mNumChildren; ++i) {
		std::cout << "nr node " << i << std::endl;

		auto vec = processNode(node->mChildren[i], scene);
		meshes.insert(meshes.end(), vec.begin(), vec.end());
	}
	return meshes;
}

std::shared_ptr<Mesh> cote::AssetManager::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<unsigned> indicies;

	for (GLuint i = 0; i < mesh->mNumVertices; ++i) 
	{
		aiVector3D currentAiVec = mesh->mVertices[i];
		glm::vec3 vec(currentAiVec.x, currentAiVec.y, currentAiVec.z);
		positions.push_back( vec);

		if (mesh->mNormals) {

			currentAiVec = mesh->mNormals[i];
			vec = glm::vec3(currentAiVec.x, currentAiVec.y, currentAiVec.z);
			normals.push_back( vec);
		}

		//bitangens etc
	}

	std::vector<aiVector3D> aiVec;

	std::copy(mesh->mTextureCoords[0], mesh->mTextureCoords[0] + mesh->mNumVertices, std::back_inserter(aiVec));
	for (auto uv : aiVec) 
	{
		glm::vec2 tc;
		tc.x = uv.x;
		tc.y = uv.y;
		uvs.push_back(tc);
	}

	for (GLuint i = 0; i<mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j<face.mNumIndices; j++)
		{
			indicies.push_back(face.mIndices[j]);
		}
	}

	auto pos = std::make_shared<cote::graphic::VertexAttribute3f>(cote::graphic::VertexAttributeIndex::POSITION, positions);
	auto uv = std::make_shared<cote::graphic::VertexAttribute2f>(cote::graphic::VertexAttributeIndex::UV_0, uvs);
	auto norm = std::make_shared<cote::graphic::VertexAttribute3f>(cote::graphic::VertexAttributeIndex::NORMAL, normals);

	cote::graphic::VertexAttributeLayout vLayout;
	vLayout.pushVertexAttribute(pos);
	vLayout.pushVertexAttribute(norm);
	vLayout.pushVertexAttribute(uv);


	auto vertexArray = std::make_shared<cote::graphic::VertexArray>(indicies, vLayout);

	auto material = std::make_shared<Material>(program);

	auto newMesh = std::make_shared<Mesh>(material, vertexArray);
	newMesh->setName(mesh->mName.C_Str());
	
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* aiMat = scene->mMaterials[mesh->mMaterialIndex];
		auto tex = loadTexture(aiMat, aiTextureType_DIFFUSE, "texture_diffuse1");
		if (tex) material->addTexture(tex);
		
		auto tex2 = loadTexture(aiMat, aiTextureType_SPECULAR, "texture_specular1");
		if(tex2) material->addTexture(tex2);
		
	}

	return newMesh;
}

std::shared_ptr<Texture> cote::AssetManager::loadTexture( aiMaterial * material, aiTextureType type, std::string typeName)
{
	size_t size = material->GetTextureCount(type);
	if (size <= 0) return nullptr;
	else
	{
		for (size_t i = 0; i < size; ++i)
		{
			aiString name;
			material->GetTexture(type, i, &name);
			std::string tmp = directory;
			tmp += name.C_Str();

			auto texIt = textures.find(tmp);
			if (texIt == textures.end())
			{
				Bitmap bitmap = cote::graphic::Bitmap(tmp);
				std::shared_ptr<Texture> texture = std::make_shared<Texture2d>(bitmap);
				texture->setSamplerName(typeName);
				textures.insert(std::make_pair(tmp, texture));
				return texture;
			}
			else
				return texIt->second;

		}
	}	
}
