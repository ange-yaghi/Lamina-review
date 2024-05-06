#version 460 core

layout (location = 0) in vec3 vertexPosition_modelspace;
layout (location = 1) in vec2 inTexture;
uniform vec4 passedColor;

out vec4 fragColour;
out vec2 textureCoordinates;

void main()
{
	fragColour = passedColor;
	textureCoordinates = inTexture;
	gl_Position.xyz = vertexPosition_modelspace;
	gl_Position.w = 1.0;
}