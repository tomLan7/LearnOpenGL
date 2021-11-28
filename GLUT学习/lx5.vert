#version 330
layout (location = 5) in vec3 Position;
uniform float testScale;
void main(){
	gl_Position = vec4(0.5*sin(testScale)* Position.x, 0.5*sin(testScale) * Position.y, Position.z*sin(testScale), 1.0);
}