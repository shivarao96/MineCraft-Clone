#version 330 core

out vec4 FragColor;
in vec3 TexCoords;

uniform samplerCube texSampler;

void main() {
	FragColor = texture(texSampler, TexCoords);
}