#version 330 core

in vec3 ourColor;

uniform float red;
uniform float blue;
uniform float yellow;

out vec4 fragColor;

void main()
{
	fragColor = vec4(ourColor,1.0) + vec4(red, blue, yellow, 0.0);
}

