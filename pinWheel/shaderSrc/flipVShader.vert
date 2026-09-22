#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in float aIndex;

out vec3 ourColor;
uniform float angle;

void main()
{
	float newAngle = radians(72) * aIndex + angle;
	float newX = -aPos.x * cos(newAngle) - aPos.y * sin(newAngle);
	float newY = aPos.y * sin(newAngle) + aPos.y * cos(newAngle);
	gl_Position = vec4(newX, newY, aPos.z, 1);
	ourColor = aColor;
}
