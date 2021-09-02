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
	//列向量
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	//无参生成的是零矩阵
	glm::mat4 trans;
	//变换矩阵和位移向量，生成 位移矩阵
	trans = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0f));
	glm::mat4 myScalingMatrix = glm::scale(glm::mat4(1.0f),glm::vec3(2.0f, 2.0f, 2.0f));
	vec = trans * vec;
	cout << vec << endl;

	auto vec2 = myScalingMatrix * vec;
	cout << vec2 << endl;

	//基于某个线性变换，逆时针旋转90度。旋转轴为z轴 。旋转以弧度为单位
	trans = glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	cout << trans*vec2<<endl;

	//将矩阵转换为可以传入uniform的格式
	auto OPenGLLikeValue=glm::value_ptr(trans);
	return 0;
}