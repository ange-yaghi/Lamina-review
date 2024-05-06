#version 460 core
in vec4 fragColour;
in vec2 textureCoordinates;

out vec4 color;

uniform sampler2D inTexture;
uniform sampler2D inTexture2;

void main(){
	color = mix(texture(inTexture, textureCoordinates), texture(inTexture2, textureCoordinates), 0.5) * fragColour;
}