#version 460 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec4 vertexColor;
layout(location = 3) in vec2 vertexUv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

struct VS_OUT{
	vec4 color;
	vec3 worldNormal;
	vec3 worldPosition;
	vec2 uv;
};

struct LightSetting {
	int type;
	vec3 color;
	vec3 position;
	vec3 direct;
};

out VS_OUT vertexOut;
uniform LightSetting lightSource[16];

void main() {

	//    FragPos = vec3(model * vec4(aPos, 1.0));
	vec4 worldPosition = modelMatrix * vec4(vertexPosition, 1.0);
	vertexOut.worldPosition = worldPosition.xyz / worldPosition.w;
	vertexOut.worldNormal = mat3(projectionMatrix * viewMatrix)* mat3(transpose(inverse(modelMatrix))) * vertexNormal;
	//vertexOut.worldNormal = nomalize(vertexOut.worldNormal);
	vertexOut.color = vertexColor;
	vertexOut.uv = vertexUv;
	//vertexOut.color = vec4(lightSource[0].color,1.0);
	gl_Position = projectionMatrix * viewMatrix * modelMatrix*vec4(vertexPosition, 1.0);
}