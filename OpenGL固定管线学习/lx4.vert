#version 330
layout (location = 0) in vec3 Position;
void main(){
	gl_Position = vec4(0.5 * Position.xyz, 1.0);
}