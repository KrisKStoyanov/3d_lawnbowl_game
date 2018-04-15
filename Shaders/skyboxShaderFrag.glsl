#version 430 core

in vec3 texCoordsExport;

out vec4 colorsOut;

uniform samplerCube cubemap;

void main()
{
	colorsOut = texture(cubemap, texCoordsExport);
}