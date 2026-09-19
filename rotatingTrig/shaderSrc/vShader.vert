#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float rot;
uniform float cenX;
uniform float cenY;

out vec3 ourColor;

void main()
{
	vec2 trans = aPos.xy - vec2(cenX, cenY);
	vec2 rotated;
	rotated.x = trans.x * cos(rot) - trans.y * sin(rot);
	rotated.y = trans.x * sin(rot) + trans.y * cos(rot);

	rotated = rotated + vec2(cenX, cenY);

	gl_Position = vec4(rotated, aPos.z, 1.0);

	ourColor = aColor;
}
