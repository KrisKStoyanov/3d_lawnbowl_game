#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Light.h"
#include "CustomShader.h"
#include "Texture.h"
#include "Lightmap.h"
#include "PhysicsObject.h"
#include "Model.h"

class GameObject
{
public:

	//Visual Effect instantiator
	GameObject(std::string _name, glm::vec3 _position, glm::vec3 _direction);

	//Physical Object instantiator
	GameObject(std::string _name, glm::vec3 _position, glm::vec3 _direction, Mesh* _mesh, Texture* _texture, Material* _material, CustomShader* _shader, PhysicsObject* _physObj = nullptr);
	
	//3D Model instantiator
	GameObject(std::string _name, glm::vec3 position, glm::vec3 direction, Model* _model, CustomShader* _shader);

	~GameObject();

	std::string name;

	glm::vec3 position;
	glm::vec3 direction;

	glm::mat4 modelMatrix;

	//Component class - virtual interface
	//store a vector with all components

	//GameObject properties
	Mesh* mesh = nullptr;
	Texture* texture = nullptr;
	Lightmap* lightmap = nullptr;
	Material* material = nullptr;
	CustomShader* customShader = nullptr;
	PhysicsObject* physObj = nullptr;
	Model* model = nullptr;

	virtual void Draw();
	virtual void Setup();
	virtual void Update(int deltaTime);
};

