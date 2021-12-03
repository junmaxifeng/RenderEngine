#version 460 core

uniform sampler2D _MainTex;

struct VS_OUT {
	vec3 uv;
};

in VS_OUT vertexOut;
out vec4 fragColor;

void main()
{
	float phi = atan(vertexOut.uv.z, vertexOut.uv.x);
	float theta = atan(vertexOut.uv.y, vertexOut.uv.x / cos(phi));

	float v = (theta + 3.1415926535897932384626 / 2) / 3.1415926535897932384626;
	float u = (phi + 3.1415926535897932384626) /(2* 3.1415926535897932384626);

	//fragColor = geoOut.color;
	//fragColor = vec4(geoOut.uv,0.0,1.0);
	fragColor= texture(_MainTex, vec2(u,v));
	//fragColor = vec4(1.0,0.0,0.0,1.0);
};