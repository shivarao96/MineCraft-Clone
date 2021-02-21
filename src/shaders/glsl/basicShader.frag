#version 440 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D texSampler;

void main() {
	FragColor = texture(texSampler, TexCoords);
}