#pragma once
#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#pragma comment(lib, "glew32.lib") 
#endif

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Camera.h"
#include "Material.h"
#include "Light.h"
#include "Texture.h"
#include "Lightmap.h"

#include "DirLight.h"
#include "SpotLight.h"
#include "PointLight.h"

class CustomShader
{
public:
	CustomShader(const GLchar *vertexPath, const GLchar *fragmentPath);
	~CustomShader();

	GLuint shaderProgramId;
	GLuint modelMatLoc;
	GLuint viewMatLoc;
	GLuint projMatLoc;
	GLuint matMatLoc;
	//GLuint diffuseTexLoc;
	//GLuint specularTexLoc;

	GLuint textureLoc;

	GLuint dirLightDirLoc;
	GLuint pointLightPosLoc;

	GLuint spotLightPosLoc;
	GLuint spotLightDirLoc;

	GLuint viewPosLoc;

	void Setup();

	void LoadTexture(Texture* texture);
	//void LoadLightmap(Lightmap* lightmap);
	void UpdateView(Camera* camera);
	void UpdateModel(glm::mat4 modelMat);
	void UpdateDirLight(DirLight* light);
	void UpdatePointLight(PointLight* light);
	void UpdateSpotLight(SpotLight* light);
	void UpdateMaterial(Material* material);

	//void PrepMaterial(Material* material);
	//void PrepLight(Light* light);
};

