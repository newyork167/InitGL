#version 330 core
out vec4 gl_FragColor;

#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float random (vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233)))*43758.5453123);
}

void main()
{
	gl_FragColor = vec4(sin(u_time), cos(u_time), 0.0, 1.0);
}