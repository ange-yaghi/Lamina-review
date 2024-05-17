#version 460 core

in vec2 textureCoordinatesToFrag;
uniform sampler2D textureData;
uniform vec4 colorToFrag;

out vec4 color;

void main()
{
	color = texture(textureData, textureCoordinatesToFrag) * colorToFrag;
}