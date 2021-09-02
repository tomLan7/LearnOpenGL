#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<iostream>
using namespace std;
ostream& operator<<(ostream& out, glm::vec4 vec) {
	cout << "x:" << vec.x << "\ty:" << vec.y << "\tz:" << vec.z ;
	return out;
}
int main() {
	//������
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	//�޲����ɵ��������
	glm::mat4 trans;
	//�任�����λ������������ λ�ƾ���
	trans = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0f));
	glm::mat4 myScalingMatrix = glm::scale(glm::mat4(1.0f),glm::vec3(2.0f, 2.0f, 2.0f));
	vec = trans * vec;
	cout << vec << endl;

	auto vec2 = myScalingMatrix * vec;
	cout << vec2 << endl;

	//����ĳ�����Ա任����ʱ����ת90�ȡ���ת��Ϊz�� ����ת�Ի���Ϊ��λ
	trans = glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	cout << trans*vec2<<endl;

	//������ת��Ϊ���Դ���uniform�ĸ�ʽ
	auto OPenGLLikeValue=glm::value_ptr(trans);
	return 0;
}