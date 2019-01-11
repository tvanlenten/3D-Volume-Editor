#version 430 core

in vec2 uv;
out vec4 FragColor;

uniform float time;
uniform vec3 test;

void main() {
	vec3 col = vec3(uv, sin(time)*0.5+0.5);
	col = mix(col, test, 0.5);
	FragColor = vec4(col, 1.0);
}