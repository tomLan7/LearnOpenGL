#pragma once
//先定义任意视角的相机，下一步定义FPS相机，最后想办法抽象出相机父类
//相机的原理就是管理 视图view矩阵的变化。
class WeightlessnessCamera
{
	glm::mat4 viewRotation;
	glm::mat4 viewMove;
	glm::mat4 view;
public:
	WeightlessnessCamera():viewRotation(1),viewMove(1),view(glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.0f, -3.0f))) {

	}
	glm::mat4 ToViewMatrix() {
		return viewMove*viewRotation*view;
	}
	void Update(float) {

	}
	void keyOrder(int key);
	void mouseOrder(float offsetX, float offsetY);
};
//先使用自带的lookat，成功后再试试用自己的lookat
class FPSCamera {
	glm::vec3 up;
	glm::vec3 target;
	glm::vec3 pos;

public:
	FPSCamera():up(0,0,1),target(0,1,0),pos(0,0,0){
	}
	/*vec3 getRightVector() {
		return glm::normalize(glm::cross(target,up));
	}
	vec3 getUpVector() {
		return glm::normalize(glm::cross(getRightVector(),target));
	}*/
	glm::vec3 face(){
		return glm::normalize(target-pos);
	}
	glm::mat4 ToViewMatrix() {
		return  glm::lookAt(pos,target,up);
	}
	void keyOrder(int key);
	void mouseOrder(float offsetX, float offsetY);
};
class EulerFPSCamera {

};