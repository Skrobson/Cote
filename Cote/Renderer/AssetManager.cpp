#include "AssetManager.h"


#include <iostream>



using namespace cote::graphic;
using namespace cote;


AssetManager::AssetManager()
{
}


AssetManager::~AssetManager()
{
}



std::shared_ptr<Model> cote::AssetManager::loadModel(const std::string & filePath, std::shared_ptr<ShaderProgram>) //aiPostProcessSteps
{
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
	for (size_t i = 0; i < node->mNumMeshes; ++i) {
		size_t index = node->mMeshes[i];
		aiMesh* mesh = scene->mMeshes[index];
		meshes.push_back(processMesh(mesh, scene));
	}
	for (size_t i = 0; i < node->mNumChildren; ++i) {
		auto vec = processNode(node->mChildren[i], scene);
		meshes.assign(vec.begin(), vec.end());
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

		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			uvs.push_back( vec);
		}
		//bitangens etc
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
		auto tex = loadTexture(aiMat, aiTextureType_DIFFUSE, TEX_DIFFUSE);
		if (tex) material->addTexture(tex);
		
		tex = loadTexture(aiMat, aiTextureType_SPECULAR, TEX_SPECULAR);
		if(tex) material->addTexture(tex);

	}

	return newMesh;
}

std::shared_ptr<Texture> cote::AssetManager::loadTexture( aiMaterial * material, aiTextureType type, std::string typeName)
{
	size_t size = material->GetTextureCount(type);
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

			textures.insert(std::make_pair(tmp, texture));
			return texture;
		}
		else
			return texIt->second;

	}

}
