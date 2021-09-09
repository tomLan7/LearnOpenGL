#pragma once
//先定义任意视角的相机，下一步定义FPS相机，最后想办法抽象出相机父类
//相机的原理就是管理 视图view矩阵的变化。
#include<iostream>
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
public:
	glm::vec3 up;
	glm::vec3 target;
	glm::vec3 pos;

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
public:
	glm::vec3 up;
	glm::vec3 pos;

	float Pitch=0,Roll=0, Yaw = 0;//X,Y,Z旋转的角。翻滚，俯航，偏航

	EulerFPSCamera() :up(0, 0, 1), pos(0, 0, 0) {
	}
	glm::vec3 target() {
		return direction()+pos;
	}
	glm::vec3 direction() {
		return glm::normalize(glm::vec3(cos(Yaw), sin(Yaw), sin(Pitch)));
	}
	glm::vec3 face() {
		return glm::normalize(target() - pos);
	}
	glm::mat4 ToViewMatrix() {
		return  glm::lookAt(pos, target(), up);
	}
	void keyOrder(int key);
	void mouseOrder(float offsetX, float offsetY);
	void PitchAdd(float value) {
		Pitch += value;
		if (Pitch > glm::radians(90.0f)) Pitch = glm::radians(90.0f);

		if (Pitch < glm::radians(-90.0f)) Pitch = glm::radians(-90.0f);
		std::cout << Pitch << std::endl;
	}
	void RollAdd(float value) {
		Roll += value;
	}
	void YawAdd(float value) {
		Yaw += value;
	}
};