#version 330 core

layout (location = 0) in vec3 aPos;
uniform float air;

void main()
{
	vec3 pos = aPos;
	pos.x += air;
	pos.y += air;

	pos.x = mod(pos.x + 1.0 , 2.0) - 1.0;
	pos.y = mod(pos.y + 1.0 , 2.0) - 1.0;
	gl_Position = vec4(pos, 1.0);
}
