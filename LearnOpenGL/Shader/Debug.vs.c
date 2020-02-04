#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 FragPos;
// out float aaa;

void main() {
	// aaa = 111.11;
	gl_Position =  vec4(aPos, 1.0);
	FragPos = aPos;
}