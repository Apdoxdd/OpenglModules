#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;
uniform float xOffSet;
uniform float yOffSet;


void main()
{
	float newX = aPos.x + xOffSet;
	float newY = aPos.y + yOffSet;
	gl_Position = vec4(newX, newY, aPos.z, 1.0); 
	texCoord = aTexCoord;
}
