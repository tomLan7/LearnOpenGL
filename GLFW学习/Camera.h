#pragma once
//�ȶ��������ӽǵ��������һ������FPS����������취������������
//�����ԭ����ǹ��� ��ͼview����ı仯��
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
//��ʹ���Դ���lookat���ɹ������������Լ���lookat
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