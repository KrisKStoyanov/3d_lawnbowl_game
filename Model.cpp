#include "Model.h"

Model::Model(std::string path)
{
	LoadModel(path);
}

Model::~Model()
{
}

Texture Model::TextureFromFile(const GLchar *path, std::string directory)
{
	Texture texture;

	std::string filename = std::string(path);
	//filename = directory + '/' + filename;
	glGenTextures(1, &texture.textureIndex);

	texture.image = getbmp(filename);

	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, texture.textureIndex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.image->sizeX, texture.image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.image);
	//glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}

void Model::LoadModel(std::string& path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices );
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));
	ProcessNode(scene->mRootNode, scene);
}

void Model::Draw(glm::mat4 model)
{
	for (GLuint i = 0; i < meshes.size(); i++) {
		meshes[i].DrawElemTexMesh(model);
	}
}

void Model::ProcessNode(aiNode * node, const aiScene * scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}
	for (GLuint i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	for (GLuint i = 0; i < mesh->mNumVertices; i++) {

		Vertex vert;
		glm::vec3 vector3;

		//Position coordinates
		vector3.x = mesh->mVertices[i].x;
		vector3.y = mesh->mVertices[i].y;
		vector3.z = mesh->mVertices[i].z;
		vert.coords = glm::vec4(vector3,1.0f);

		//Normals
		vector3.x = mesh->mNormals[i].x;
		vector3.y = mesh->mNormals[i].y;
		vector3.z = mesh->mNormals[i].z;
		vert.normal = vector3;

		//Texture coordinates
		if (mesh->mTextureCoords[0]) {
			glm::vec2 vector2;
			vector2.x = mesh->mTextureCoords[0][i].x;
			vector2.y = mesh->mTextureCoords[0][i].y;
			vert.uv = vector2;
		}
		else {
			vert.uv = glm::vec2(0.0f, 0.0f);
		}

		//Default color
		vert.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		vertices.push_back(vert);

		for (GLuint i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for (GLuint j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}

		if (mesh->mMaterialIndex >= 0) {
			modelMatColData = new Material(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 32);
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			aiColor3D matColor (0.0f, 0.0f, 0.0f);

			material->Get(AI_MATKEY_COLOR_AMBIENT, matColor);
			modelMatColData->ambRefl.r = matColor.r;
			modelMatColData->ambRefl.g = matColor.g;
			modelMatColData->ambRefl.b = matColor.b;

			material->Get(AI_MATKEY_COLOR_AMBIENT, matColor);
			modelMatColData->difRefl.r = matColor.r;
			modelMatColData->difRefl.g = matColor.g;
			modelMatColData->difRefl.b = matColor.b;

			material->Get(AI_MATKEY_COLOR_AMBIENT, matColor);
			modelMatColData->specRefl.r = matColor.r;
			modelMatColData->specRefl.g = matColor.g;
			modelMatColData->specRefl.b = matColor.b;

			material->Get(AI_MATKEY_SHININESS, modelMatColData->shininess);

			std::vector<Texture> matTex = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
			textures.insert(textures.end(), matTex.begin(), matTex.end());
		}

	}

	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial * mat, aiTextureType type)
{
	std::vector<Texture> textures;

	for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture texture(std::string(str.C_Str()), true); //= TextureFromFile(str.C_Str(), directory);
		//Texture texture = TextureFromFile(str.C_Str(), directory);
		//texture = str;
		textures.push_back(texture);
	} 
	return textures;
}
