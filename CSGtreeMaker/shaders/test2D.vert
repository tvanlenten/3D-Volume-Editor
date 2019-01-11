#version 430 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

out vec2 uv;

uniform vec2 pos;
uniform vec2 scale;
uniform float aspectRatio;

void main() {
	uv = texCoords;

	vec2 p = position * scale;

    gl_Position = vec4(p, 0.0, 1.0); 
} 