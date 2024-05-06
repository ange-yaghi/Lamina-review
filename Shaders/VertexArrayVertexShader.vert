#version 460 core

layout (location = 0) in vec4 vertexLoaction;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 textureCoordinates;

out vec4 colorToFrag;
out vec3 normalToFrag;
out vec2 textureToFrag;

uniform vec4 color;

void main()
{
	gl_Position = vertexLoaction;
	colorToFrag = color;
	normalToFrag = normals;
	textureToFrag = textureCoordinates;
}