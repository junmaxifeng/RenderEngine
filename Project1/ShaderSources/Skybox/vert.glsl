#version 460 core
layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec3 vertexUv;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

struct VS_OUT {
	vec3 uv;
};

out VS_OUT vertexOut;

void main() {
	vertexOut.uv = vertexUv;
	gl_Position = vec4(vertexPosition,0.99, 1.0);
}