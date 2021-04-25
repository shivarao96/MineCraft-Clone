#version 330 core

layout(location = 0) in vec3 aChunkPos;
layout(location = 1) in vec2 aChunkTex;
layout(location = 2) in float aCardinalLight;

out vec2 ChunkTexCoords;
out float CardinalLight;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * vec4(aChunkPos, 1.0); 
	ChunkTexCoords = aChunkTex;
	CardinalLight = aCardinalLight;
}