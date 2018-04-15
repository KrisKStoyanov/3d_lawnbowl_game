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
#include <iostream>
#include <fstream>
#include <vector>

#include "GameObject.h"
#include "vertex.h"
#include "shader.h"
#include "getbmp.h"
#include "Texture.h"
#include "Skybox.h"

#include "Camera.h"
#include "Cubemap.h"

#include "MeshManager.h"
#include "LightManager.h"
#include "MaterialManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "CameraManager.h"

#include "PhysicsEngine.h"

#include "GameManager.h"
#include "SplashScreen.h"

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	void Setup();
	void Initialise(int w_Width, int w_Height, const char* w_Title, int argc, char **argv);
	void Start();

	static int windowWidth;
	static int windowHeight;

	static void Update();
	static void Display();
	static void Resize(int w_Width, int w_Height);
	static void SpecialKeyInput(int key, int x, int y);

	static void KeyCallback(unsigned char key, int action, int mode);
	static void KeyReleaseCallback(unsigned char key, int action, int mode);
	static void MouseCallback(int xPos, int yPos);

	static std::vector<GameObject*> gameObjects;

	void AddGameObject(GameObject* gameobject, bool camFollow);
	GameObject* FindGameObject(std::string gameObjectName);

	static int deltaTime;

	static GameObject* cameraFollow;

	static int oldTimeSinceStart;
	static int newTimeSinceStart;
	static float fps;
	static int frameRate;
	static int frameTime;

	static Camera* mainCamera;
	static Skybox* skybox;

	static MeshManager meshManager;
	static LightManager lightManager;
	static MaterialManager materialManager;
	static TextureManager textureManager;
	static ShaderManager shaderManager;
	static CameraManager cameraManager;

	static PhysicsEngine physEngine;

	static GameManager gameManager;
	static SplashScreen splashScreen;

	static void AddPhysObject(PhysicsObject* physObject);

	static void shaderCompileTest(GLuint shader);
};

