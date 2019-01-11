#version 430 core

in vec2 uv;
out vec4 FragColor;

uniform float time;

void main() {
	FragColor = vec4(uv, sin(time)*0.5+0.5, 1.0);
}