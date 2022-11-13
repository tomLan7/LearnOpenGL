#version 330
layout (location = 5) in vec3 Position;
uniform mat4 gMat;
out vec4 Color;
void main(){
	gl_Position = gMat*vec4(Position,1.0);
	Color=vec4(Position,1);
}