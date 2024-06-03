#version 460 core

layout (location = 0) in vec4 verticeLocation;
layout (location = 1) in vec2 textureCoordinates;

uniform mat4 translationMatrix;
uniform mat4 rotationMatrix;
uniform mat4 scaleMatrix;

out vec2 textureCoordinatesToFrag;

void main()
{
	gl_Position = translationMatrix * rotationMatrix * scaleMatrix * verticeLocation;
	textureCoordinatesToFrag = textureCoordinates;
}