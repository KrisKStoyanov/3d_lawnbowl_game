#include "Skybox.h"

Skybox::Skybox(Cubemap* cubemap)
{
	skyCubemap = cubemap;
}


Skybox::~Skybox()
{

}

void Skybox::Setup()
{
	skyboxVertices = std::vector<Vertex>({
		{ { -10.0, -10.0, -10.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },{ 0.0, 0.0 },{ 0.0, 0.0, 1.0 } }, //0
		{ { 10.0, -10.0, -10.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 } ,{ 1.0, 0.0 } ,{ 0.0, 0.0, 1.0 } }, //1
		{ { 10.0, 10.0, -10.0, 1.0 },{ 1.0, 1.0,1.0, 1.0 } ,{ 1.0, 1.0 } ,{ 0.0, 0.0, 1.0 } }, //2
		{ { -10.0, 10.0, -10.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 } ,{ 0.0, 1.0 } ,{ 0.0, 0.0, 1.0 } }, //3
		{ { -10.0, -10.0, 10.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },{ 0.0, 0.0 },{ 0.0, 0.0, 1.0 } }, //4
		{ { 10.0, -10.0, 10.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 } ,{ 1.0, 0.0 } ,{ 0.0, 0.0, 1.0 } }, //5
		{ { 10.0, 10.0, 10.0, 1.0 },{ 1.0, 1.0,1.0, 1.0 } ,{ 1.0, 1.0 } ,{ 0.0, 0.0, 1.0 } }, //6
		{ { -10.0, 10.0, 10.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 } ,{ 0.0, 1.0 } ,{ 0.0, 0.0, 1.0 } } //7
		});

	skyboxIndices = std::vector<GLuint>({ 
		3,0,1,1,2,3 ,
		5,0,3,3,6,4 ,
		1,5,6,6,2,1 ,
		4,7,6,6,5,4 ,
		3,2,6,6,7,3 ,
		0,4,1,1,4,5 });

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * skyboxVertices.size(), skyboxVertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * skyboxIndices.size(), skyboxIndices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(skyboxVertices[0]), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(skyboxVertices[0]), (GLvoid*)sizeof(skyboxVertices[0].coords));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(skyboxVertices[0]), (GLvoid*)(sizeof(skyboxVertices[0].coords) + sizeof(skyboxVertices[0].color)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(skyboxVertices[0]), (GLvoid*)(sizeof(skyboxVertices[0].coords) + sizeof(skyboxVertices[0].color) + sizeof(skyboxVertices[0].uv)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
}

void Skybox::Draw(Camera* mainCamera, CustomShader* shader)
{
	//glDepthMask(GL_FALSE);
	glUseProgram(shader->shaderProgramId);
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyCubemap->textureId);
	glUniform1i(glGetUniformLocation(cubemapLoc, "mainTex"), 0);
	glDrawElements(GL_TRIANGLES, skyboxIndices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	//glDepthMask(GL_TRUE);
}
