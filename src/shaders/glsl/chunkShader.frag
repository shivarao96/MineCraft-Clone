#version 330 core

out vec4 FragColor;
in vec2 ChunkTexCoords;
in float CardinalLight;

uniform sampler2D sampler;

void main() {
	FragColor = texture(sampler, ChunkTexCoords) * CardinalLight;	
	if(FragColor.a == 0) discard;
}