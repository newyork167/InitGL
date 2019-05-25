#version 330 core
layout (location = 0)

in vec3 aPos;

uniform float u_mouse_dot_product;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 0);
}