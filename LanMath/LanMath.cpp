// LanMath.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include"HomogeneousCoordinates4F.h"
#include"Matrix4F.h"
#include"Quaternion.h"
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
void testQuaternion() {
	Quaternion q1({50,50,24});
	cout << q1 << endl;
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
