#version 430 core

in vec2 uv;
out vec4 FragColor;

uniform float f;

void main() {
	FragColor = vec4(uv, f, 1.0);
}