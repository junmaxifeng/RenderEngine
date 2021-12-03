#version 460 core

uniform sampler2D _MainTex;

struct VS_OUT {
	vec4 color;
	vec3 worldNormal;
	vec3 worldPosition;
	vec2 uv;
};

in VS_OUT geoOut;
out vec4 fragColor;

void main()
{
	//fragColor = geoOut.color;
	//fragColor = vec4(geoOut.uv,0.0,1.0);
	fragColor= texture(_MainTex, geoOut.uv);
	//fragColor = vec4(1.0,0.0,0.0,1.0);
};