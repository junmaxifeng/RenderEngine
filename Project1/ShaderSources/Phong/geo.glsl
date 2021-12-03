#version 460 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

struct VS_OUT {
	vec4 color;
	vec3 worldNormal;
	vec3 worldPosition;
	vec2 uv;
};

in VS_OUT tessEvalOut[];
out VS_OUT geoOut;

void main() {
	gl_Position = gl_in[0].gl_Position;
	geoOut = tessEvalOut[0];
	EmitVertex();

	gl_Position = gl_in[1].gl_Position;
	geoOut = tessEvalOut[1];
	EmitVertex();

	gl_Position = gl_in[2].gl_Position;
	geoOut = tessEvalOut[2];
	EmitVertex();

	EndPrimitive();
}