#version 430 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec4 colorsExport;
in vec2 texCoordsExport;
in vec3 normalsExport;

in vec3 fragPos;

float diff, spec;

vec3 ambient, diffuse, specular;

vec3 normals, lightDir, viewDir, reflDir;

uniform sampler2D mainTex;
uniform Material mainMat;
uniform Light mainLight;
uniform vec3 viewPos;

vec3 estLightColor;

out vec4 colorsOut;

void main(void)
{
  colorsOut = texture(mainTex, texCoordsExport) * colorsExport;
}