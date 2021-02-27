#version 440 core

out vec4 FragColor;
in vec2 ChunkTexCoords;

uniform sampler2D sampler;

void main() {
	FragColor = texture(sampler, ChunkTexCoords);	
}