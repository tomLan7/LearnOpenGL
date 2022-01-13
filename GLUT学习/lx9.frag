#version 330
out vec4 FragColor;

void main(){
	FragColor = vec4(gl_FragCoord.z*0.5+0.5,gl_FragCoord.z*0.5+0.5,gl_FragCoord.z*0.5+0.5,1);
}