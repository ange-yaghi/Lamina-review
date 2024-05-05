#version 460 core
in vec4 fragColour;
out vec4 idiot;
in float fragTime;
void main(){
	idiot = fragColour;
}