#include "AssetManager.h"


#include <iostream>
#include <GlobalLogger.h>
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
		
		auto model = std::make_shared<Model>(meshes);
		models.insert(std::make_pair( filePath, model));

		DEBUG_LOG("model", filePath, "loaded");

		return model;
	}
	else
		return modelIterator->second;

	
}

std::vector<std::shared_ptr<Mesh>> cote::AssetManager::processNode(aiNode * node, const aiScene * scene)
{
	std::vector<std::shared_ptr<Mesh>> meshes;

	std::for_each(node->mMeshes, node->mMeshes + node->mNumMeshes, [&](size_t index)
	{
		meshes.push_back(processMesh( scene->mMeshes[index], scene));
	});
	
	std::for_each(node->mChildren, node->mChildren + node->mNumChildren, [&](aiNode * node)
	{
		auto vec = processNode(node, scene);
		meshes.insert(meshes.end(), vec.begin(), vec.end());
	});

	return meshes;
}

std::shared_ptr<Mesh> cote::AssetManager::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<unsigned> indicies;

	auto numVertices = mesh->mNumVertices;

	auto vector3dConversion = [](const aiVector3D & aiVec)->glm::vec3
	{
		return glm::vec3(aiVec.x, aiVec.y, aiVec.z);
	};

	std::transform(mesh->mVertices, mesh->mVertices + numVertices, std::back_inserter(positions),vector3dConversion);
	std::transform(mesh->mNormals, mesh->mNormals + numVertices, std::back_inserter(normals), vector3dConversion);

		//bitangens etc
	
	std::transform(mesh->mTextureCoords[0], mesh->mTextureCoords[0] + mesh->mNumVertices, std::back_inserter(uvs), [](const aiVector3D & aiUv)->glm::vec2
	{
		glm::vec2 uv;
		uv.x = aiUv.x;
		uv.y = aiUv.y;
		return uv;
	});

	std::for_each(mesh->mFaces, mesh->mFaces + mesh->mNumFaces, [& indicies](const aiFace& face)
	{
		std::copy(face.mIndices, face.mIndices + face.mNumIndices, std::back_inserter(indicies));
	});

	auto pos = std::make_shared<cote::graphic::VertexAttribute3f>(cote::graphic::VertexAttributeIndex::POSITION, positions);
	auto uv = std::make_shared<cote::graphic::VertexAttribute2f>(cote::graphic::VertexAttributeIndex::UV_0, uvs);
	auto norm = std::make_shared<cote::graphic::VertexAttribute3f>(cote::graphic::VertexAttributeIndex::NORMAL, normals);

	cote::graphic::VertexAttributeLayout vLayout;
	vLayout.pushVertexAttribute(pos);
	vLayout.pushVertexAttribute(norm);
	vLayout.pushVertexAttribute(uv);

	std::shared_ptr<VertexArray> vertexArray;
	try
	{
		vertexArray = std::make_shared<cote::graphic::VertexArray>(indicies, vLayout);
	}
	catch (GlException & ex)
	{
		FATAL_ERROR_LOG(ex.what());
		return nullptr;
	}

	auto material = std::make_shared<Material>(program);

	auto newMesh = std::make_shared<Mesh>(material, vertexArray);
	newMesh->setName(mesh->mName.C_Str());
	
	//refactor
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
