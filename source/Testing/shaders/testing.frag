#version 330 core
out vec4 gl_FragColor;

uniform float u_time;
uniform float u_mouse_dot_product;
uniform float u_mouse_x;
uniform float u_mouse_y;

void main()
{
	gl_FragColor = vec4(sin(u_mouse_x), cos(u_mouse_y), 0.5, 1.0);
}