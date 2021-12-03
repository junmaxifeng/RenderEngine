
#version 460 core

layout(quads, equal_spacing, ccw) in;

struct VS_OUT {
	vec4 color;
	vec3 worldNormal;
	vec3 worldPosition;
	vec2 uv;
};

in VS_OUT tessConOut[];
out VS_OUT tessEvalOut;

vec2 quadInterpolation(vec2 input0, vec2 input1, vec2 input2, vec2 input3) {
	float u = gl_TessCoord.x;
	float omu = 1 - u;
	float v = gl_TessCoord.y;
	float omv = 1 - v;
	vec2 ret;
	ret = omu * omv*input0 +
		u * omv*input1 +
		u * v*input2 +
		omu * v*input3;
	return ret;
}
vec3 quadInterpolation(vec3 input0, vec3 input1, vec3 input2, vec3 input3) {
	float u = gl_TessCoord.x;
	float omu = 1 - u;
	float v = gl_TessCoord.y;
	float omv = 1 - v;
	vec3 ret;
	ret = omu * omv*input0 +
		u * omv*input1 +
		u * v*input2 +
		omu * v*input3;
	return ret;
}
vec4 quadInterpolation(vec4 input0, vec4 input1, vec4 input2, vec4 input3) {
	float u = gl_TessCoord.x;
	float omu = 1 - u;
	float v = gl_TessCoord.y;
	float omv = 1 - v;
	vec4 ret;
	ret= omu * omv*input0 +
		u * omv*input1 +
		u * v*input2 +
		omu * v*input3;
	return ret;
}

void main(void)
{
	gl_Position = quadInterpolation(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_in[2].gl_Position, gl_in[3].gl_Position);
	tessEvalOut.uv = quadInterpolation(tessConOut[0].uv, tessConOut[1].uv, tessConOut[2].uv, tessConOut[3].uv);
	tessEvalOut.color = quadInterpolation(tessConOut[0].color, tessConOut[1].color, tessConOut[2].color, tessConOut[3].color);
	tessEvalOut.worldNormal = quadInterpolation(tessConOut[0].worldNormal, tessConOut[1].worldNormal, tessConOut[2].worldNormal, tessConOut[3].worldNormal);
	tessEvalOut.worldPosition = quadInterpolation(tessConOut[0].worldPosition, tessConOut[1].worldPosition, tessConOut[2].worldPosition, tessConOut[3].worldPosition);
}