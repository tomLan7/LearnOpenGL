#pragma once
#include"HomogeneousCoordinates4F.h"
#include<algorithm>
#include <vector>
#include<ConstantDef.h>
namespace lan {
	struct Matrix4F {

		HomogeneousCoordinates4F data[4];//4�����������ֱ��Ӧ�þ�����������
		Matrix4F() {
			data[0] = { 1,0,0,0 };
			data[1] = { 0,1,0,0 };
			data[2] = { 0,0,1,0 };
			data[3] = { 0,0,0,1 };
		};
		Matrix4F(HomogeneousCoordinates4F d1, HomogeneousCoordinates4F d2, HomogeneousCoordinates4F d3, HomogeneousCoordinates4F d4) {
			data[0] = d1;
			data[1] = d2;
			data[2] = d3;
			data[3] = d4;
		}

		Matrix4F transpose() {
			Matrix4F returnValue = *this;
			returnValue.transposed();
			return returnValue;
		}
		//ת��
		void transposed() {
			//����ÿ����
			for (int i = 0; i < 4; i++) {
				//����ÿ��
				for (int j = i+1; j <4;j++ ) {
					std::swap(data[i][j],data[j][i]);
				}
			}
		}
		bool operator==(const Matrix4F& mat)const {
			for (int i = 0; i < sizeof(data) / sizeof(data[0]);i++) {
				if (data[i] != mat[i]) {
					return false;
				}
			}
			return true;
		}
		HomogeneousCoordinates4F operator*(const HomogeneousCoordinates4F& vec)const{
			HomogeneousCoordinates4F result;
			for (int i = 0; i < sizeof(data)/sizeof(data[0]);i++) {
				result+=data[i] * vec[i];
			}
			return result;
		}
		Matrix4F operator*(const Matrix4F& mat)const {
			Matrix4F result;
			for (int i = 0; i < 4;i++) {
				result[i]=(*this)*mat[i];
			}
			return result;
		}
		HomogeneousCoordinates4F& operator[](size_t index) {
			return data[index];
		}
		const HomogeneousCoordinates4F& operator[](size_t index)const {
			return data[index];
		}

		static Matrix4F Translate(Vector3F translate) {
			return Matrix4F{ {1,0,0,0},{0,1.f,0,0},{0,0,1.f,0},{translate,1} };
		}
		static Matrix4F Scale(Vector3F scale) {
			return Matrix4F{ {scale.x,0,0,0},{0,scale.y,0,0},{0,0,scale.z,0},{0,0,0,1} };
		}
		//������ʱ����ת
		static Matrix4F RotationX(float radian) {
			Vector3F newY = { 0,1,0 };
			Vector3F newZ = { 0,0,1 };
			newY.rotateX(-radian);
			newZ.rotateX(-radian);
			return Matrix4F({ 1,0,0,0 }, { newY, 0 }, { newZ,0 }, { 0,0,0,1 });
		}
		static Matrix4F RotationY(float radian) {
			Vector3F newZ = { 0,0,1 };
			Vector3F newX = { 1,0,0 };
			newZ.rotateY(-radian);
			newX.rotateY(-radian);
			return Matrix4F({ newX,0 }, {0,1,0, 0 }, {newZ,0 }, { 0,0,0,1 });
		}
		static Matrix4F RotationZ(float radian) {
			Vector3F newX = { 1,0,0 };
			Vector3F newY = { 0,1,0 };
			newX.rotateZ(-radian);
			newY.rotateZ(-radian);
			return Matrix4F({ newX,0 }, { newY, 0 }, { 0,0,1,0 }, { 0,0,0,1 });
		}
		//ŷ��������ת����
		static Matrix4F Rotate(Vector3F rotate) {
			return RotationZ(rotate.z)*RotationY(rotate.y)*RotationX(rotate.x);
		}
		static Matrix4F FaceTo(Vector3F face,Vector3F up) {
			Matrix4F returnValue;
			Vector3F N = face.unit();//��Ӧ������ϵZ��
			Vector3F U = Vector3F::cross(up, face).unit();//��Ӧ������ϵX��
			Vector3F V = Vector3F::cross(N, U);//��Ӧ������ϵY��
			returnValue[0] = Vector4F(U, 0);
			returnValue[1] = Vector4F(V, 0);
			returnValue[2] = Vector4F(N, 0);
			returnValue[3] = Vector4F(0, 0, 0, 1);
			return returnValue.transpose();
		}
		static Matrix4F OrthoProjTransform(float left, float right, float bottom, float top, float zNear, float zFar) {
			float width = right - left;
			float height = top - bottom;
			float deep = zFar - zNear;
			float xMid = (right + left) / 2;
			float yMid = (top + bottom) / 2;
			float zMid = (zFar + zNear) / 2;
			/*
			Vector4F newX(2/width,0,0,0);
			Vector4F newY(0,2/height,0,0);
			Vector4F newZ(0,0,2/deep,0);
			Vector4F newW(-xMid/width,-yMid / height,-zMid / deep,1);
			return Matrix4F(newX, newY, newZ, newW);*/
			//����zֵ�������Dx����Ӧ����1/deep����ΪDx��NDC��z�᷶ΧΪ0~1.
			return Scale({ 2 / width,2 / height,2/ deep}) * Translate({ -xMid,-yMid,-zMid });
		}


		static Matrix4F PersProjTransform(float FOV, float aspectRatio, float zNear, float zFar) {

			Matrix4F returnValue;
			const float ar = aspectRatio;//���ݱ�
			const float zRange = zNear - zFar;
			const float tanHalfFOV = tanf(ToRadian(FOV / 2.0));

			returnValue[0][0] = 1.0f / (tanHalfFOV * ar);
			returnValue[0][1] = 0.0f;
			returnValue[0][2] = 0.0f;
			returnValue[0][3] = 0.0f;

			returnValue[1][0] = 0.0f;
			returnValue[1][1] = 1.0f / tanHalfFOV;
			returnValue[1][2] = 0.0f;
			returnValue[1][3] = 0.0f;

			returnValue[2][0] = 0.0f;
			returnValue[2][1] = 0.0f;
			returnValue[2][2] = (-zNear - zFar) / zRange;
			returnValue[2][3] = 1.0f;//��w����z��zԽ��wԽ��

			returnValue[3][0] = 0.0f;
			returnValue[3][1] = 0.0f;
			returnValue[3][2] = 2.0f * zFar * zNear / zRange;
			returnValue[3][3] = 0.0f;
			return returnValue;
		}

		static Matrix4F frustum(float left,float right,float bottom,float top,float near,float far){

		}
		static Matrix4F lookAt(lan::Vector3F eye, lan::Vector3F center, lan::Vector3F up) {
			return {};
		}
		//ʹ�ø�˹��Ԫ��
		float Determinant() {
			Matrix4F temp_data=*this;
			float rate = 1;
			for (int i = 0; i < 4;i++) {
				int y = i;
				for (; temp_data[y][i] == 0; y++);
				if (y == 4) {//��һ��ȫ��0
					return 0;
				}
				if (y != i) {
					rate = -rate;//��������ʽ����
					std::swap(temp_data[i],temp_data[y]);
				}
				//��Ԫ��ȡ����
				rate *= temp_data[i][i];
				temp_data[i] /= temp_data[i][i];//��λ��
				for (int j = i+1; j < 4;j++) {
					temp_data[j] -= temp_data[i] * temp_data[j][i];//��ȥ����Ԫ
				}
			}
			return rate;
		}
		//ʹ�ó��ȴ�����
		Matrix4F Inverse() {
			Matrix4F temp_data = *this;
			//һ����λ����
			Matrix4F return_matrix;
			for (int i = 0; i < 4; i++) {
				int y = i;
				for (; temp_data[y][i] == 0; y++);
				if (y == 4) {//��һ��ȫ��0
					throw std::exception("���ǿ������");
				}
				if (y != i) {
					std::swap(temp_data[i], temp_data[y]);
					std::swap(return_matrix[i], return_matrix[y]);
				}
				//Ҫô������Ԫ��ֵ��Ҫô�Ȳ���return_matrix[i]���Ȳ���temp_data�Ļ���Ԫֵ�ͱ���
				return_matrix[i] /= temp_data[i][i];
				temp_data[i] /= temp_data[i][i];
				
				for (int j = i + 1; j < 4; j++) {
					return_matrix[j] -= return_matrix[i] * temp_data[j][i];
					temp_data[j] -= temp_data[i] * temp_data[j][i];//��ȥ����Ԫ
				}
			}
			return return_matrix;
		}

		bool IsOrthogonal() {
			return (*this * this->transpose())==Matrix4F();
		}
	};
}
