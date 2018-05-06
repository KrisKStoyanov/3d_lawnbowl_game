#include "GameEngine.h"

std::vector<GameObject*> GameEngine::gameObjects;

GameObject* GameEngine::cameraFollow;

int GameEngine::oldTimeSinceStart;
int GameEngine::newTimeSinceStart;

float GameEngine::fps = 0;
int GameEngine::frameRate = 0;
int GameEngine::frameTime;

MeshManager GameEngine::meshManager;
LightManager GameEngine::lightManager;
MaterialManager GameEngine::materialManager;
TextureManager GameEngine::textureManager;
ShaderManager GameEngine::shaderManager;
CameraManager GameEngine::cameraManager;

ModelManager GameEngine::modelManager;

PhysicsEngine GameEngine::physEngine;

int GameEngine::windowWidth;
int GameEngine::windowHeight;

int GameEngine::deltaTime;

Camera* GameEngine::mainCamera;
Skybox* GameEngine::skybox;

GameManager GameEngine::gameManager;
SplashScreen GameEngine::splashScreen;

GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::Setup()
{
	glClearColor(0.55f, 0.55f, 0.55f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	//GAME MANAGER: (LAWN BOWL)
	//------------

	gameManager.Setup(2, 0, 3, glm::vec3(0.0, 6.0, 90.0));

	//CAMERAS:
	//-------

	cameraManager.UploadCamera("FirstCamera", new Camera(glm::vec3(0.0, 20.0, 120.0), glm::vec3(0.0, 0.0 ,-1.0),0.5,0.25));
	cameraManager.UploadCamera("SecondaryCamera", new Camera(glm::vec3(0.0, 15.0, 0.0), glm::vec3(0.0, 0.0, -1.0), 0.5,0.25));
	cameraManager.UploadCamera("ThirdCamera", new Camera(glm::vec3(-100.0, 5.0, 0.0), glm::vec3(-1.0, 0.0, 0.0),0.5,0.25));

	mainCamera = cameraManager.GetCamera("FirstCamera");
	mainCamera->Setup(windowWidth, windowHeight);

	//SPLASH SCREEN: (INSTRUCTIONS)
	//-------------
	splashScreen.Setup(mainCamera->GetPosition(), "./Resources/instructions.bmp");

	//MESHES:
	//------

	//Grass Field:
	meshManager.UploadMesh("GrassMesh", new Mesh(std::vector<Vertex>({
		{ { 500.0, 0.0, 500.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },{ 25.0, 0.0 },{ 0.0, 1.0, 0.0 } },
		{ { 500.0, 0.0, -500.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 } ,{ 25.0, 25.0 } ,{ 0.0, 1.0, 0.0 } },
		{ { -500.0, 0.0, 500.0, 1.0 },{ 1.0, 1.0,1.0, 1.0 } ,{ 0.0, 0.0 } ,{ 0.0, 1.0, 0.0 } },
		{ { -500.0, 0.0, -500.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 } ,{ 0.0, 25.0 } ,{ 0.0, 1.0, 0.0 } }
		}), std::vector<GLuint>({ 0,1,2,3 })));

	//Dirt Field:
	meshManager.UploadMesh("FieldMesh", new Mesh(std::vector<Vertex>({
		{ { 500.0, 0.0, 50.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },{ 25.0, 0.0 },{ 0.0, 1.0, 0.0 } },
		{ { 500.0, 0.0, -50.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 } ,{ 25.0, 2.5 } ,{ 0.0, 1.0, 0.0 } },
		{ { -500.0, 0.0, 50.0, 1.0 },{ 1.0, 1.0,1.0, 1.0 } ,{ 0.0, 0.0 } ,{ 0.0, 1.0, 0.0 } },
		{ { -500.0, 0.0, -50.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 } ,{ 0.0, 2.5 } ,{ 0.0, 1.0, 0.0 } }
		}), std::vector<GLuint>({ 0,1,2,3 })));

	//Stone Boundaries:
	meshManager.UploadMesh("Boundaries", new Mesh(std::vector<Vertex>({
		{ { 500.0, 0.0, -600.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },{ 40.0, 0.0 },{ mainCamera->GetPosition().x,mainCamera->GetPosition().y,mainCamera->GetPosition().z } }, //0
		{ { 500.0, 40.0, -600.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 } ,{ 40.0, 1.0 } ,{ mainCamera->GetPosition().x,mainCamera->GetPosition().y,mainCamera->GetPosition().z } }, //1
		{ { -500.0, 0.0, -600.0, 1.0 },{ 1.0, 1.0,1.0, 1.0 } ,{ 0.0, 0.0 } ,{ mainCamera->GetPosition().x,mainCamera->GetPosition().y,mainCamera->GetPosition().z } }, //2
		{ { -500.0, 40.0, -600.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 } ,{ 0.0, 1.0 } ,{ mainCamera->GetPosition().x,mainCamera->GetPosition().y,mainCamera->GetPosition().z } }, //3
		{ { -500.0, 0.0, 500.0, 1.0 },{ 1.0, 1.0,1.0, 1.0 } ,{ 40.0, 0.0 } ,{ mainCamera->GetPosition().x,mainCamera->GetPosition().y,mainCamera->GetPosition().z } }, //4
		{ { -500.0, 40.0, 500.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 } ,{ 40.0, 1.0 } ,{ mainCamera->GetPosition().x,mainCamera->GetPosition().y,mainCamera->GetPosition().z } }, //5
		{ { 500.0, 0.0, 500.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },{ 0.0, 0.0 },{ mainCamera->GetPosition().x,mainCamera->GetPosition().y,mainCamera->GetPosition().z } }, //6
		{ { 500.0, 40.0, 500.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 } ,{ 0.0, 1.0 } ,{ mainCamera->GetPosition().x,mainCamera->GetPosition().y,mainCamera->GetPosition().z } }, //7

		{ { 500.0, 40.0, -620.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },{ 40.0, 0.0 },{ 0.0, 0.0, 1.0 } }, //8
		{ { -500.0, 40.0, -620.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 } ,{ 0.0, 0.0 } ,{ 0.0, 0.0, 1.0 } }, //9

		}), std::vector<GLuint>({ 0,1,2,3,2,3,4,5,4,5,6,7,6,7,0,1 
		,1,8,3,9})));

	//Skybox:
	meshManager.UploadMesh("SBFront", new Mesh(std::vector<Vertex>({
		{ { 1000.0, -1000.0, -1000.0, 1.0 },{ 1.0, 1, 1.0, 1 },{ 1.0, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 1000.0, 1000.0, -1000.0, 1.0 },{ 1.0, 1, 1, 1 } ,{ 1.0, 1.0 } ,{ 1.0, 1.0, 1.0 } },
		{ { -1000.0, -1000.0, -1000.0, 1.0 },{ 1.0,1.0,1, 1 } ,{ 0.0, 0.0 } ,{ 1.0, 1.0, 1.0 } },
		{ { -1000.0, 1000.0, -1000.0, 1.0 },{ 1.0, 1.0, 1.0, 1 } ,{ 0.0, 1.0 } ,{ 1.0, 1.0, 1.0 } }
	}), std::vector<GLuint>({ 0,1,2,3 })));

	meshManager.UploadMesh("SBBack", new Mesh(std::vector<Vertex>({
		{ { 1000.0, -1000.0, 1000.0, 1.0 },{ 1.0, 1, 1.0, 1 },{ 1.0, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 1000.0, 1000.0, 1000.0, 1.0 },{ 1.0, 1, 1, 1 } ,{ 1.0, 1.0 } ,{ 1.0, 1.0, 1.0 } },
		{ { -1000.0, -1000.0, 1000.0, 1.0 },{ 1.0,1.0,1, 1 } ,{ 0.0, 0.0 } ,{ 1.0, 1.0, 1.0 } },
		{ { -1000.0, 1000.0, 1000.0, 1.0 },{ 1.0, 1.0, 1.0, 1 } ,{ 0.0, 1.0 } ,{ 1.0, 1.0, 1.0 } }
	}), std::vector<GLuint>({ 0,1,2,3 })));

	meshManager.UploadMesh("SBLeft", new Mesh(std::vector<Vertex>({
		{ { -1000.0, -1000.0, -1000.0, 1.0 },{ 1.0, 1, 1.0, 1 },{ 1.0, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { -1000.0, 1000.0, -1000.0, 1.0 },{ 1.0, 1, 1, 1 } ,{ 1.0, 1.0 } ,{ 1.0, 1.0, 1.0 } },
		{ { -1000.0, -1000.0, 1000.0, 1.0 },{ 1.0,1.0,1, 1 } ,{ 0.0, 0.0 } ,{ 1.0, 1.0, 1.0 } },
		{ { -1000.0, 1000.0, 1000.0, 1.0 },{ 1.0, 1.0, 1.0, 1 } ,{ 0.0, 1.0 } ,{ 1.0, 1.0, 1.0 } }
	}), std::vector<GLuint>({ 0,1,2,3 })));

	meshManager.UploadMesh("SBRight", new Mesh(std::vector<Vertex>({
		{ { 1000.0, -1000.0, 1000.0, 1.0 },{ 1.0, 1, 1.0, 1 },{ 1.0, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 1000.0, 1000.0, 1000.0, 1.0 },{ 1.0, 1, 1, 1 } ,{ 1.0, 1.0 } ,{ 1.0, 1.0, 1.0 } },
		{ { 1000.0, -1000.0, -1000.0, 1.0 },{ 1.0,1.0,1, 1 } ,{ 0.0, 0.0 } ,{ 1.0, 1.0, 1.0 } },
		{ { 1000.0, 1000.0, -1000.0, 1.0 },{ 1.0, 1.0, 1.0, 1 } ,{ 0.0, 1.0 } ,{ 1.0, 1.0, 1.0 } }
	}), std::vector<GLuint>({ 0,1,2,3 })));

	meshManager.UploadMesh("SBTop", new Mesh(std::vector<Vertex>({
		{ { 1000.0, 1000.0, -1000.0, 1.0 },{ 1.0, 1, 1.0, 1 },{ 1.0, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 1000.0, 1000.0, 1000.0, 1.0 },{ 1.0, 1, 1, 1 } ,{ 1.0, 1.0 } ,{ 1.0, 1.0, 1.0 } },
		{ { -1000.0, 1000.0, -1000.0, 1.0 },{ 1.0,1.0,1, 1 } ,{ 0.0, 0.0 } ,{ 1.0, 1.0, 1.0 } },
		{ { -1000.0, 1000.0, 1000.0, 1.0 },{ 1.0, 1.0, 1.0, 1 } ,{ 0.0, 1.0 } ,{ 1.0, 1.0, 1.0 } }
	}), std::vector<GLuint>({ 0,1,2,3 })));

	meshManager.UploadMesh("SBBottom", new Mesh(std::vector<Vertex>({
		{ { 1000.0, -1000.0, 1000.0, 1.0 },{ 1.0, 1, 1.0, 1 },{ 1.0, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 1000.0, -1000.0, -1000.0, 1.0 },{ 1.0, 1, 1, 1 } ,{ 1.0, 1.0 } ,{ 1.0, 1.0, 1.0 } },
		{ { -1000.0, -1000.0, 1000.0, 1.0 },{ 1.0,1.0,1, 1 } ,{ 0.0, 0.0 } ,{ 1.0, 1.0, 1.0 } },
		{ { -1000.0, -1000.0, -1000.0, 1.0 },{ 1.0, 1.0, 1.0, 1 } ,{ 0.0, 1.0 } ,{ 1.0, 1.0, 1.0 } }
	}), std::vector<GLuint>({ 0,1,2,3 })));

	//Sphere data:
	meshManager.UploadSphereMesh("MediumSphere", 30, 30, 4);

	meshManager.UploadSphereMesh("SmallSphere", 30, 30, 2);

	//TEXTURES:
	//---------

	//Objects:
	textureManager.UploadTexture("BasicMetal", new Texture("./Resources/diffuseBall.bmp", true));
	textureManager.UploadTexture("DustyMetal", new Texture("./Resources/diffuseBall2.bmp", true));
	textureManager.UploadTexture("ShinyMetal", new Texture("./Resources/toonJackBall.bmp", true));

	//Game Zone:
	textureManager.UploadTexture("Grass", new Texture("./Resources/greenTex.bmp", true));
	textureManager.UploadTexture("Field", new Texture("./Resources/fieldTex.bmp", true));
	textureManager.UploadTexture("Stone", new Texture("./Resources/toonStone.bmp", true));

	//Skybox:
	textureManager.UploadTexture("SBFront", new Texture("./Resources/Skybox/sbFront.bmp", false));
	textureManager.UploadTexture("SBLeft", new Texture("./Resources/Skybox/sbLeft.bmp", false));
	textureManager.UploadTexture("SBRight", new Texture("./Resources/Skybox/sbRight.bmp", false));
	textureManager.UploadTexture("SBTop", new Texture("./Resources/Skybox/sbTop.bmp", false));
	textureManager.UploadTexture("SBBottom", new Texture("./Resources/Skybox/sbBottom.bmp", false));
	textureManager.UploadTexture("SBBack", new Texture("./Resources/Skybox/sbBack.bmp", false));

	//LIGHTING:
	//--------

	lightManager.UploadLight("DirectLight", new DirLight(glm::vec3(0.4f, -1.0f, -0.4f), glm::vec3(0.35f, 0.35f, 0.35f), glm::vec3(0.35f, 0.35f, 0.35f), glm::vec3(0.7f, 0.7f, 0.7f)));
	lightManager.UploadLight("PointLight", new PointLight(glm::vec3(0.0, 25.0, -750.0), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.8, 0.8, 0.8), glm::vec3(1.0, 1.0, 1.0), 1.0f, 0.09f, 0.032f));
	lightManager.UploadLight("SpotLight", new SpotLight(glm::vec3(0.0, 50.0, -750.0), glm::vec3(0.0, -10.0, 10.0), glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 1.0f, 0.09f, 0.032f));
	
	//MATERIALS:
	//----------

	materialManager.UploadMaterial("basic", new Material(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 16.0f));
	materialManager.UploadMaterial("reflective", new Material(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f));
	materialManager.UploadMaterial("dim", new Material(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.6f, 0.6f, 0.6f), glm::vec3(0.3f, 0.3f, 0.3f), 1.0f));

	//MODELS:
	//-------

	modelManager.UploadModel("Clubhouse", new Model("./Resources/Models/clubhouse_textured_optimized.obj"));
	//modelManager.UploadModel("Warehouse", new Model("./Resources/Models/toonWarehouse.obj"));

	//CUBEMAP SKYBOX:
	//--------------

	skybox = new Skybox(new Cubemap("./Resources/Skybox/sbRight.bmp", "./Resources/Skybox/sbLeft.bmp", "./Resources/Skybox/sbTop.bmp", "./Resources/Skybox/sbBottom.bmp", "./Resources/Skybox/sbBack.bmp", "./Resources/Skybox/sbFront.bmp"));
	skybox->Setup();

	//SHADERS:
	//-------

	CustomShader* shader = new CustomShader("./Shaders/vertexShader.glsl", "./Shaders/fragmentShader.glsl");
	CustomShader* shader1 = new CustomShader("./Shaders/vertexShader1.glsl", "./Shaders/fragmentShader1.glsl");
	CustomShader* shader2 = new CustomShader("./Shaders/vertexShader2.glsl", "./Shaders/fragmentShader2.glsl");
	CustomShader* shader3 = new CustomShader("./Shaders/cellShadedVert.glsl", "./Shaders/cellShadedFrag.glsl");
	CustomShader* shader4 = new CustomShader("./Shaders/cellShadedOutlineVert.glsl", "./Shaders/cellShadedOutlineFrag.glsl");
	CustomShader* shader5 = new CustomShader("./Shaders/vertexShaderNoTex.glsl", "./Shaders/fragmentShaderNoTex.glsl");

	shaderManager.UploadShader("lit", shader);
	shaderManager.UploadShader("errorMagenta", shader1);
	shaderManager.UploadShader("unlit", shader2);
	shaderManager.UploadShader("toon", shader3);
	shaderManager.UploadShader("toonOutline", shader4);
	shaderManager.UploadShader("baseColor", shader5);
}

void GameEngine::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mainCamera->UpdateViewMatrix();
	splashScreen.Draw(shaderManager.GetShader("unlit"));
	//skybox->Draw(mainCamera,shaderManager.GetShader("unlit"));
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->customShader->UpdateView(mainCamera);
		gameObjects[i]->customShader->UpdateModel(gameObjects[i]->modelMatrix);
		gameObjects[i]->customShader->UpdateDirLight(lightManager.GetDirLight("DirectLight"));
		gameObjects[i]->customShader->UpdatePointLight(lightManager.GetPointLight("PointLight"));
		gameObjects[i]->customShader->UpdateSpotLight(lightManager.GetSpotLight("SpotLight"));
		gameObjects[i]->customShader->UpdateMaterial(gameObjects[i]->material);
		gameObjects[i]->Draw();
	}

	glutSwapBuffers();
}

void GameEngine::Update()
{
	oldTimeSinceStart = newTimeSinceStart;
	newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);

	deltaTime = newTimeSinceStart - oldTimeSinceStart;

	GameEngine::frameRate++;
	if (GameEngine::newTimeSinceStart - GameEngine::frameTime > 200) {
		fps = GameEngine::frameRate * 1000.0 / (GameEngine::newTimeSinceStart - GameEngine::frameTime);
		frameTime = newTimeSinceStart;
		GameEngine::frameRate = 0;
		std::cout << "FPS: " << fps << std::endl;
	}

	if (deltaTime == 0) {
		Sleep(1);
		newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
		deltaTime = newTimeSinceStart - oldTimeSinceStart;
	}

	physEngine.HandlePhysics(deltaTime);

	for (std::vector<GameObject*>::size_type i = 0; i != gameObjects.size(); i++) {
		gameObjects[i]->Update(deltaTime);
	}

	physEngine.HandleCollisions();

	if (gameManager.currentBall->physObj->velocity == glm::vec3(0.0, 0.0, 0.0) && !gameManager.nextThrowReady && !gameManager.gameOver) {
		gameManager.nextThrowReady = true;
		gameManager.LocateCurrentBall();
	}
	else if (gameManager.currentBall->physObj->velocity == glm::vec3(0.0, 0.0, 0.0) && gameManager.gameOver && !gameManager.declaredWin) {
		gameManager.SettleGame();
	}

	glutPostRedisplay();
}

void GameEngine::Resize(int width, int height)
{
	glViewport(0, 0, width, height);
}

void GameEngine::Initialise(int width, int height, const char* title, int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(title);
	//glutFullScreen();

	windowWidth = width;
	windowHeight = height;

	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutIdleFunc(Update);
	glutSpecialFunc(SpecialKeyInput);
	glutKeyboardFunc(KeyCallback);
	glutKeyboardUpFunc(KeyReleaseCallback);
	glutPassiveMotionFunc(MouseCallback);

	glutSetCursor(GLUT_CURSOR_NONE);
	glutWarpPointer(windowWidth / 2, windowHeight / 2);

	glewExperimental = GL_TRUE;
	glewInit();
}

void GameEngine::Start()
{
	glutMainLoop();
}

void GameEngine::SpecialKeyInput(int key, int x, int y)
{
	splashScreen.active = false;

	if (key == GLUT_KEY_UP) {
		
	}
	if (key == GLUT_KEY_DOWN) {
		
	}
	if (key == GLUT_KEY_LEFT) {
		if (gameManager.currentBall != nullptr && gameManager.currentBall->physObj->velocity == glm::vec3(0.0, 0.0, 0.0) && !gameManager.gameOver) {
			gameManager.currentBall->physObj->position.x -= 1.0f;
		}
	}
	if (key == GLUT_KEY_RIGHT) {
		if (gameManager.currentBall != nullptr && gameManager.currentBall->physObj->velocity == glm::vec3(0.0, 0.0, 0.0) && !gameManager.gameOver) {
			gameManager.currentBall->physObj->position.x += 1.0f;
		}
	}
}

void GameEngine::KeyCallback(unsigned char key, int action, int mode)
{
	splashScreen.active = false;

	if (key == 27) {
		cameraManager.CleanMemory();
		lightManager.CleanMemory();
		materialManager.CleanMemory();
		meshManager.CleanMemory();
		shaderManager.CleanMemory();
		textureManager.CleanMemory();
		modelManager.CleanMemory();
		exit(0);
	}

	if (key == 'w') {
		mainCamera->ProcessKeyboard(FORWARD, deltaTime);
	}
	if (key == 's') {
		mainCamera->ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (key == 'a') {
		mainCamera->ProcessKeyboard(LEFT, deltaTime);
	}
	if (key == 'd') {
		mainCamera->ProcessKeyboard(RIGHT, deltaTime);
	}
	if (key == 'r') {
		mainCamera->ProcessKeyboard(VIEW_UP, deltaTime);
	}
	if (key == 'f') {
		mainCamera->ProcessKeyboard(VIEW_DOWN, deltaTime);
	}

	if (key == 'e') {
		mainCamera->ProcessKeyboard(VIEW_RIGHT, deltaTime);
	}
	if (key == 'q') {
		mainCamera->ProcessKeyboard(VIEW_LEFT, deltaTime);
	}
	if (key == '1') {
		mainCamera = cameraManager.GetCamera("FirstCamera");
		mainCamera->Setup(windowWidth, windowHeight);
	}
	if (key == '2') {
		mainCamera = cameraManager.GetCamera("SecondaryCamera");
		mainCamera->Setup(windowWidth, windowHeight);
	}
	if (key == '3') {
		mainCamera = cameraManager.GetCamera("ThirdCamera");
		mainCamera->Setup(windowWidth, windowHeight);
	}
	if (key == ' ') {
		gameManager.prepThrow = true;

		if (gameManager.inactiveJack) {
			gameManager.ThrowJack();
		}
		else {
			gameManager.ThrowBall();
		}
	}

	if (key == 't') {
		std::cout << gameManager.backhand << std::endl;
		gameManager.SwapThrowhand();
	}

	if (key == 'm') {
		gameManager.prepRot += 1.0f;
		std::cout << gameManager.prepRot << std::endl;
	}

	if (key == 'n') {
		gameManager.prepRot -= 1.0f;
		std::cout << gameManager.prepRot << std::endl;
	}
}

void GameEngine::KeyReleaseCallback(unsigned char key, int action, int mode)
{
	if (key == ' ') {
		gameManager.prepThrow = false;
		if (gameManager.inactiveJack) {
			gameManager.ThrowJack();
			gameManager.inactiveJack = false;
		}
		else {
			gameManager.ThrowBall();
		}
	}
}

void GameEngine::MouseCallback(int xPos, int yPos)
{
	//glutWarpPointer(windowWidth / 2, windowHeight / 2);

	//mainCamera->lastX = windowWidth / 2;
	//mainCamera->lastY = windowHeight / 2;

	if (mainCamera->firstMouse) {
		mainCamera->lastX = xPos;
		mainCamera->lastY = yPos;
		mainCamera->firstMouse = false;
	}

	GLfloat xOffset = xPos - mainCamera->lastX;
	GLfloat yOffset = mainCamera->lastY - yPos;

	mainCamera->lastX = xPos;
	mainCamera->lastY = yPos;

	if (xPos >= windowWidth - 20) {
		glutWarpPointer(windowWidth - 20, yPos);
	}
	
	if (xPos <= 20) {
		glutWarpPointer(20, yPos);
	}

	if (yPos >= windowHeight - 20) {
		glutWarpPointer(xPos, windowHeight - 20);
	}

	if (yPos <= 20) {
		glutWarpPointer(xPos, 20);
	}

	mainCamera->ProcessMouseMovement(xOffset, yOffset, false);
}

void GameEngine::AddGameObject(GameObject* gameobject, bool camFollow)
{
	gameObjects.push_back(gameobject);
	gameobject->Setup();
	if (camFollow) {
		cameraFollow = gameobject;
	}
}

void GameEngine::AddPhysObject(PhysicsObject* physObject)
{
	physEngine.physicsObjects.push_back(physObject);
}

GameObject* GameEngine::FindGameObject(std::string gameObjectName)
{
	for (int i = 0; i < gameObjects.size(); i++) {
		if (gameObjects[i]->name == gameObjectName) {
			return gameObjects[i];
		}
	}
}

void GameEngine::shaderCompileTest(GLuint shader)
{
	GLint result = GL_FALSE;
	int logLength; glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<GLchar> vertShaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(shader, logLength, NULL, &vertShaderError[0]);
	std::cout << &vertShaderError[0] << std::endl;
}
