#version 460 core

layout (location = 0) in vec3 vertexPosition_modelspace;
layout (location = 1) in vec4 color;
uniform float currentTime;

out vec4 fragColour;
out float fragTime;
void main()
{
	fragColour = vec4(abs(sin(currentTime)) * color.x, abs(sin(currentTime + 2.0944)) * color.y, abs(sin(currentTime + 2.0944*2)) * color.z, color.w);
	gl_Position.xyz = vertexPosition_modelspace;
	gl_Position.w = 1.0;
	fragTime = currentTime;
}