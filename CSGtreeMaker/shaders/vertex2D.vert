#version 430 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

out vec2 uv;

void main() {
	uv = texCoords;
    gl_Position = vec4(position, 0.0, 1.0); 
} 