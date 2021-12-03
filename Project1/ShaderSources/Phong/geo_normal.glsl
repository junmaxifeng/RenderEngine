#version 460 core
layout(triangles) in;
layout(line_strip, max_vertices = 8) out;

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

	gl_Position = gl_in[0].gl_Position+0.1*vec4(tessEvalOut[0].worldNormal,0.0f);
	geoOut = tessEvalOut[0];
	EmitVertex();
	EndPrimitive();

	gl_Position = gl_in[1].gl_Position;
	geoOut = tessEvalOut[1];
	EmitVertex();

	gl_Position = gl_in[1].gl_Position + 0.1*vec4(tessEvalOut[1].worldNormal, 0.0f);
	geoOut = tessEvalOut[1];
	EmitVertex();
	EndPrimitive();

	gl_Position = gl_in[2].gl_Position;
	geoOut = tessEvalOut[2];
	EmitVertex();

	gl_Position = gl_in[2].gl_Position + 0.1*vec4(tessEvalOut[2].worldNormal, 0.0f);
	geoOut = tessEvalOut[2];
	EmitVertex();
	EndPrimitive();
}