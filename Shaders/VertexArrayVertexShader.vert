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
uniform mat4 rotationMatrix_x;
uniform mat4 rotationMatrix_y;
uniform mat4 rotationMatrix_z;
uniform mat4 projectionMatrix;

void main()
{
	mat4 roationMatrix = rotationMatrix_x * rotationMatrix_y * rotationMatrix_z;
	gl_Position = projectionMatrix * translationMatrix * roationMatrix * scaleMatrix * vertexLoaction;

	colorToFrag = color;
	normalToFrag = normals;
	texturesToFrag = textureCoordinates;
}