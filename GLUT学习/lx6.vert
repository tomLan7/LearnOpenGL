#version 330
layout (location = 5) in vec3 Position;
uniform mat4 gScale;
uniform mat4 gTranslate;
uniform mat4 gRotate;
out vec4 Color;
void main(){
	gl_Position = gTranslate*gScale*gRotate*vec4(Position,1.0);
	Color=clamp(gl_Position,0,1) ;
}