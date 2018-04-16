#include "Model.h"

Model::Model(GLchar*path)
{
	LoadModel(path);
}


Model::~Model()
{
}

GLint Model::TextureFromFile(const char * path, std::string directory)
{
	Texture texture(directory, false);

	return texture.textureIndex;
}

void Model::LoadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));
	ProcessNode(scene->mRootNode, scene);
}

void Model::Draw(CustomShader shader, glm::mat4 model)
{
	glUseProgram(shader.shaderProgramId);
	for (GLuint i = 0; i < meshes.size(); i++) {
		meshes[i].DrawElementsMesh(model);
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
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		}
	}
	return Mesh(vertices, indices);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;

	for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);

		GLboolean skip = false;

		for (GLuint j = 0; j < loadedTextures.size(); j++) {
			if (loadedTextures[j].image->data == str.data) {
				textures.push_back(loadedTextures[j]);
				skip = true;

				break;
			}
		}

		if (!skip) {
			Texture texture(str.data, true);
			loadedTextures.push_back(texture);
		}
	} 
	return textures;
}
