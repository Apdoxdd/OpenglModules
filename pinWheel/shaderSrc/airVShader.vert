#version 330 core

layout (location = 0) in vec3 aPos;
uniform float air;

void main()
{
	gl_Position = vec4(aPos, 1.0) + vec4(air, air, 0 , 0);
}
