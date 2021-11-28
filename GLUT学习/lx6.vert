#version 330
layout (location = 5) in vec3 Position;
uniform mat4 gScale;
uniform mat4 gTranslate;
uniform mat4 gRotate;
void main(){
	gl_Position = gTranslate*gScale*gRotate*vec4(Position,1.0);
}