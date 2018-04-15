#version 430 core

layout(location=0) in vec4 objectCoords;
layout(location=1) in vec4 objectColor;
layout(location=2) in vec2 objectTexCoords;
layout(location=3) in vec3 objectNormals;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 colorsExport;
out vec2 texCoordsExport;
out vec3 normalsExport;

out vec3 fragPos;

void main(void)
{   
   colorsExport = objectColor;
   texCoordsExport = objectTexCoords;
   normalsExport = objectNormals;
   
   fragPos = vec3(model * objectCoords);

   gl_Position = projection * model * view * objectCoords;
}
