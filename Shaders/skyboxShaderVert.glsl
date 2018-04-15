#version 430 core

layout(location=0) in vec3 objectCoords;

uniform mat4 view;
uniform mat4 projection;

out vec3 texCoordsExport;

void main(void)
{   
   texCoordsExport = objectCoords;

   gl_Position = projection * view * vec4(objectCoords,1.0f);
}
