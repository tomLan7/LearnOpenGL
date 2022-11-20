// LanMath.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include"HomogeneousCoordinates4F.h"
#include"Matrix4F.h"
#include"Quaternion.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
using namespace lan;
using namespace std;
void testMatrix() {
	Vector4F a(1, 1, 1, 1);
	Matrix4F m1{ {-1,3,7,10},{-7,-3,5,10},{3,1,-1,2},{1,1,-1,2} };
	//Matrix4F m1{ {2,0,0,0},{0,2,0,0},{0,0,2,0},{0,0,0,2} };
	cout << m1.Determinant() << endl;
	auto matrix = m1.Inverse();
	for (int i = 0; i < 4; i++) {
		cout << matrix[i] << endl;
	}
	cout << matrix.Determinant() << endl;
	//cout << Matrix4F::Translate({1,5,3}) * a << endl;
}


static std::ostream& operator<<(std::ostream& out, const glm::qua<float>& q) {
	cout << q.x << "," << q.y << "," << q.z << "," << q.w << endl;
	return out;
}
void testQuaternion() {
	auto q1=Quaternion::fromEulerAngle(0,45,90);
	cout << q1 << endl;
	auto q2 = Quaternion::fromEulerAngle(0, 30, 20);
	cout << q2 << endl;
	cout << (q1*q2) << endl;
	cout << (q2 * q1) << endl;
	cout << q1.toEuler()*Rad2Deg << endl;
	cout << q2.toEuler() * Rad2Deg << endl;
	cout << (q1  * q2).toEuler() * Rad2Deg << endl;

	glm::mat4 model = glm::mat4(1.0f); //创建一个单位矩阵
	glm::qua<float> q3 = glm::qua<float>(glm::radians(glm::vec3(0.0f, 45.0f, 90.0f))); //创建一个绕z轴旋转90度的四元数
	glm::qua<float> q4 = glm::qua<float>(glm::radians(glm::vec3(0.0f, 30.0f, 20.0f))); //创建一个绕z轴旋转90度的四元数
	cout << q3 << endl;
	cout << q4 << endl;
	cout << (q3*q4) << endl;
	cout << (q4 * q3) << endl;
	cout << glm::eulerAngles(q3) * Rad2Deg << endl;
	cout << glm::eulerAngles(q4) * Rad2Deg << endl;
	cout << glm::eulerAngles(q3 * q4) * Rad2Deg << endl;
	
	//model = glm::mat4_cast(q) * model;	//得到一个旋转的模型矩阵
}
int main()
{
	testQuaternion();

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
