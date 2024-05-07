#version 460 core

in vec4 colorToFrag;
in vec3 normalsToFrag;
in vec2 texturesToFrag;

out vec4 color;

uniform sampler2D inTexture;
uniform bool textured;

void main()
{
	if(textured) color = texture(inTexture, texturesToFrag);
	else color = colorToFrag;
}