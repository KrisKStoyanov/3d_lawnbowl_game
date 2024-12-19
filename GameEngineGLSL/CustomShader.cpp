#include "CustomShader.h"

CustomShader::CustomShader(const GLchar *vertexPath, const GLchar *fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	shaderProgramId = glCreateProgram();
	glAttachShader(shaderProgramId, vertex);
	glAttachShader(shaderProgramId, fragment);
	glLinkProgram(shaderProgramId);

	if (!success) {
		glGetProgramInfoLog(shaderProgramId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	Setup();
}

CustomShader::~CustomShader()
{
}

void CustomShader::Setup()
{
	glUseProgram(shaderProgramId);
	modelMatLoc = glGetUniformLocation(shaderProgramId, "model");
	projMatLoc = glGetUniformLocation(shaderProgramId, "projection");
	viewMatLoc = glGetUniformLocation(shaderProgramId, "view");
	textureLoc = glGetUniformLocation(shaderProgramId, "mainTex");
	//diffuseTexLoc = glGetUniformLocation(shaderProgramId, "mainMat.diffuse");
	//specularTexLoc = glGetUniformLocation(shaderProgramId, "mainMat.specular");

	dirLightDirLoc = glGetUniformLocation(shaderProgramId, "dirLight.direction");
	pointLightPosLoc = glGetUniformLocation(shaderProgramId, "pointLight.position");
	spotLightPosLoc = glGetUniformLocation(shaderProgramId, "spotLight.position");
	spotLightDirLoc = glGetUniformLocation(shaderProgramId, "spotLight.direction");

	viewPosLoc = glGetUniformLocation(shaderProgramId, "viewPos");
}

void CustomShader::LoadTexture(Texture * texture)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->textureIndex);
	glUniform1i(glGetUniformLocation(textureLoc, "mainTex"), 0);
}

//void CustomShader::LoadLightmap(Lightmap * lightmap)
//{
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, lightmap->diffuseIndex);
//	glUniform1i(glGetUniformLocation(diffuseTexLoc, "mainMat.diffuse"), 0);
//
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, lightmap->specularIndex);
//	glUniform1i(glGetUniformLocation(specularTexLoc, "mainMat.specular"), 1);
//}

void CustomShader::UpdateView(Camera * camera)
{
	glUseProgram(shaderProgramId);
	glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(camera->view));
	glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(camera->projection));
	glUniform3f(viewPosLoc, camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);
}

void CustomShader::UpdateModel(glm::mat4 modelMat)
{
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
}

void CustomShader::UpdateDirLight(DirLight* light)
{
	glUniform3f(dirLightDirLoc, light->direction.x, light->direction.y, light->direction.z);
	glUniform3f(glGetUniformLocation(shaderProgramId, "dirLight.ambient"), light->ambColor.r, light->ambColor.g, light->ambColor.b);
	glUniform3f(glGetUniformLocation(shaderProgramId, "dirLight.diffuse"), light->difColor.r, light->difColor.g, light->difColor.b);
	glUniform3f(glGetUniformLocation(shaderProgramId, "dirLight.specular"), light->specColor.r, light->specColor.g, light->specColor.b);
}

void CustomShader::UpdatePointLight(PointLight * light)
{
	glUniform3f(pointLightPosLoc, light->position.x, light->position.y, light->position.z);
	glUniform3f(glGetUniformLocation(shaderProgramId, "pointLight.ambient"), light->ambColor.r, light->ambColor.g, light->ambColor.b);
	glUniform3f(glGetUniformLocation(shaderProgramId, "pointLight.diffuse"), light->difColor.r, light->difColor.g, light->difColor.b);
	glUniform3f(glGetUniformLocation(shaderProgramId, "pointLight.specular"), light->specColor.r, light->specColor.g, light->specColor.b);
	glUniform1f(glGetUniformLocation(shaderProgramId, "pointLight.constant"), light->constant);
	glUniform1f(glGetUniformLocation(shaderProgramId, "pointLight.linear"), light->linear);
	glUniform1f(glGetUniformLocation(shaderProgramId, "pointLight.quadratic"), light->quadratic);
}

void CustomShader::UpdateSpotLight(SpotLight * light)
{
	glUniform3f(spotLightDirLoc, light->direction.x, light->direction.y, light->direction.z);
	glUniform3f(spotLightPosLoc, light->position.x, light->position.y, light->position.z);
	glUniform3f(glGetUniformLocation(shaderProgramId, "spotLight.ambient"), light->ambColor.r, light->ambColor.g, light->ambColor.b);
	glUniform3f(glGetUniformLocation(shaderProgramId, "spotLight.diffuse"), light->difColor.r, light->difColor.g, light->difColor.b);
	glUniform3f(glGetUniformLocation(shaderProgramId, "spotLight.specular"), light->specColor.r, light->specColor.g, light->specColor.b);
	glUniform1f(glGetUniformLocation(shaderProgramId, "spotLight.constant"), light->constant);
	glUniform1f(glGetUniformLocation(shaderProgramId, "spotLight.linear"), light->linear);
	glUniform1f(glGetUniformLocation(shaderProgramId, "spotLight.quadratic"), light->quadratic);
	glUniform1f(glGetUniformLocation(shaderProgramId, "spotLight.cutOff"), light->cutOff);
	glUniform1f(glGetUniformLocation(shaderProgramId, "spotLight.outerCutOff"), light->outerCutOff);
}

void CustomShader::UpdateMaterial(Material * material)
{
	//glUniform1i(glGetUniformLocation(shaderProgramId, "mainMat.diffuse"), 0);
	//glUniform1i(glGetUniformLocation(shaderProgramId, "mainMat.specular"), 1);
	glUniform3f(glGetUniformLocation(shaderProgramId, "material.ambient"), material->ambRefl.r, material->ambRefl.g, material->ambRefl.b);
	glUniform3f(glGetUniformLocation(shaderProgramId, "material.diffuse"), material->difRefl.r, material->difRefl.g, material->difRefl.b);
	glUniform3f(glGetUniformLocation(shaderProgramId, "material.specular"), material->specRefl.r, material->specRefl.g, material->specRefl.b);
	glUniform1f(glGetUniformLocation(shaderProgramId, "material.shininess"), material->shininess);
}

