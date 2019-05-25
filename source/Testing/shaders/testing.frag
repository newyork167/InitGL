#version 330 core
out vec4 FragColor;

const float PI = 3.1415926535897932384626433832795;

uniform float u_time;
uniform float u_mouse_dot_product;
uniform float u_mouse_x;
uniform float u_mouse_y;

void main()
{
    FragColor = vec4(sin(u_time), cos(u_time), cos(u_time), 1.0);
}