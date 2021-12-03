#version 460 core

layout(vertices = 4) out;

struct VS_OUT{
	vec4 color;
	vec3 worldNormal;
	vec3 worldPosition;
	vec2 uv;
};

in VS_OUT vertexOut[];
out VS_OUT tessConOut[];

void main(void)
{
	if (gl_InvocationID == 0)
	{
		gl_TessLevelInner[0] = 6.0;
		gl_TessLevelInner[1] = 6.0;

		gl_TessLevelOuter[0] = 2.0;
		gl_TessLevelOuter[1] = 2.0;
		gl_TessLevelOuter[2] = 2.0;
		gl_TessLevelOuter[3] = 2.0;
	}
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	tessConOut[gl_InvocationID].uv = vertexOut[gl_InvocationID].uv;
	tessConOut[gl_InvocationID].color = vertexOut[gl_InvocationID].color;
	tessConOut[gl_InvocationID].worldNormal = vertexOut[gl_InvocationID].worldNormal;
	tessConOut[gl_InvocationID].worldPosition = vertexOut[gl_InvocationID].worldPosition;
}