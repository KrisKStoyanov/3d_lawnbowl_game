#include "SplashScreen.h"



SplashScreen::SplashScreen()
{
}


SplashScreen::~SplashScreen()
{
}

void SplashScreen::Setup(glm::vec3 cameraPosition,std::string imageAddress)
{
	vertices = std::vector<Vertex>({
		{ { cameraPosition.x + 7.5, cameraPosition.y + 7.5, cameraPosition.z - 5, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },{ 1.0, 1.0 },{ 0.0, 0.0, 1.0 } },
		{ { cameraPosition.x + 7.5, cameraPosition.y - 7.5, cameraPosition.z - 5, 1.0 },{ 1.0, 1.0, 1.0, 1.0 } ,{ 1.0, 0.0 } ,{ 0.0, 0.0, 1.0 } },
		{ { cameraPosition.x - 7.5, cameraPosition.y + 7.5, cameraPosition.z - 5, 1.0 },{ 1.0, 1.0,1.0, 1.0 } ,{ 0.0, 1.0 } ,{ 0.0, 0.0, 1.0 } },
		{ { cameraPosition.x - 7.5, cameraPosition.y - 7.5, cameraPosition.z - 5, 1.0 },{ 1.0, 1.0, 1.0, 1.0 } ,{ 0.0, 0.0 } ,{ 0.0, 0.0, 1.0 } }
		});

	indices = std::vector<GLuint>({ 0,1,2,3 });
	active = true;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)sizeof(vertices[0].coords));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)(sizeof(vertices[0].coords) + sizeof(vertices[0].color)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)(sizeof(vertices[0].coords) + sizeof(vertices[0].color) + sizeof(vertices[0].uv)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);

	image = getbmp(imageAddress);

	glGenTextures(1, &textureIndex);
	glBindTexture(GL_TEXTURE_2D, textureIndex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->sizeX, image->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image->data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void SplashScreen::Draw(CustomShader* shader)
{
	if (active) {
		glUseProgram(shader->shaderProgramId);
		glBindVertexArray(vao);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureIndex);
		glUniform1i(glGetUniformLocation(textureLoc, "mainTex"), 0);
		glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}
}
