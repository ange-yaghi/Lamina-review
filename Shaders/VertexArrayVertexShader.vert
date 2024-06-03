#version 460 core

layout (location = 0) in vec4 vertexLoaction;
layout (location = 1) in vec2 textureCoordinates;
layout (location = 2) in vec3 normals;

out vec4 colorToFrag;
out vec3 normalToFrag;
out vec2 texturesToFrag;

uniform vec4 color;

uniform mat4 translationMatrix;
uniform mat4 scaleMatrix;
uniform mat4 rotationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * (translationMatrix * rotationMatrix * scaleMatrix) * vertexLoaction;

	colorToFrag = color;
	normalToFrag = normals;
	texturesToFrag = textureCoordinates;
}