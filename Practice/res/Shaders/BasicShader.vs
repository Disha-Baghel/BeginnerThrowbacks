#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec3 offSet;

out vec2 UV;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	vec4 World = ( Model * vec4(pos,1) ) + vec4(offSet,0);
	gl_Position = Projection * View * World;
	UV = inUV;
}