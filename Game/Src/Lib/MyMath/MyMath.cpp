#include "MyMath.h"
#include <math.h>

VECTOR VecCreate(VECTOR vPosA, VECTOR vPosB)
{//ベクトル生成
	VECTOR result;
	result.x = vPosB.x - vPosA.x;
	result.y = vPosB.y - vPosA.y;
	result.z = vPosB.z - vPosA.z;
	return result;
}

float VecLong(VECTOR PosA, VECTOR PosB)
{//ベクトルの長さを返す
	float result;
	result = sqrtf((PosA.x - PosB.x) * (PosA.x - PosB.x) + (PosA.y - PosB.y) * (PosA.y - PosB.y) + (PosA.z - PosB.z) * (PosA.z - PosB.z));
	return result;
}

VECTOR VecAdd(VECTOR vecA, VECTOR vecB)
{//ベクトルの足し算
	VECTOR result;
	result.x = vecA.x + vecB.x;
	result.y = vecA.y + vecB.y;
	result.z = vecA.z + vecB.z;

	return result;
}

VECTOR VecSubtract(VECTOR vecA, VECTOR vecB)
{//ベクトルの引き算
	VECTOR result;
	result.x = vecA.x - vecB.x;
	result.y = vecA.y - vecB.y;
	result.z = vecA.z - vecB.z;

	return result;

}

VECTOR VecScale(VECTOR vec, float scale)
{//ベクトルのスカラー倍
	VECTOR result;
	result.x = vec.x * scale;
	result.y = vec.y * scale;
	result.z = vec.z * scale;

	return result;
}

float VecDot(VECTOR vecA, VECTOR vecB)
{//ベクトルの内積
	float result;
	result = vecA.x * vecB.x + vecA.y * vecB.y + vecA.z * vecB.z;
	return result;
}

VECTOR VecCross(VECTOR vecA, VECTOR vecB)
{//ベクトルの外積
	VECTOR result;
	result.x = vecA.y * vecB.z - vecA.z * vecB.y;
	result.y = vecA.z * vecB.x - vecA.x * vecB.z;
	result.z = vecA.x * vecB.y - vecA.y * vecB.x;
	return result;
}

VECTOR VecNormalize(VECTOR vec)
{//ベクトルの正規化
	float size;
	VECTOR result;
	size = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	size = sqrtf(size);
	result.x = vec.x / size;
	result.y = vec.y / size;
	result.z = vec.z / size;

	return result;
}

void Matldentity(MATRIX *mp)
{//行列生成
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(i == j)
			{
				mp->m[i][j] = 1;
			}
			else
			{
				mp->m[i][j] = 0;
			}
		}
	}
}

//MATRIX MatAdd(MATRIX matA, MATRIX matB)
//{//行列同士の加算
//	MATRIX result;
//	memset(&result, 0, sizeof(result));
//	for(int i = 0; i < 4; i++)
//	{
//		for(int j = 0; j < 4; j++)
//		{
//			result.m[i][j] = matA.m[i][j] + matB.m[i][j];
//		}
//	}
//
//	return result;
//}

MATRIX MyMatMult(MATRIX matA, MATRIX matB)
{//行列の掛け算
	MATRIX result;
	memset(&result, 0, sizeof(result));
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			for(int k = 0; k < 4; k++)
			{
				result.m[i][j] += (matA.m[i][k] * matB.m[k][j]);
			}
		}
	}

	return result;
}

//MATRIX MatScale(MATRIX mat, float scale)
//{//行列のスカラー倍
//	MATRIX result;
//	memset(&result, 0, sizeof(result));
//	for(int i = 0; i < 4; i++)
//	{
//		for(int j = 0; j < 4; j++)
//		{
//			result.m[i][j] = mat.m[i][j] * scale;
//		}
//	}
//
//	return result;
//}

VECTOR Transform(MATRIX mat, VECTOR vec)
{//ベクトル×行列
	float tVec[4];
	float rVec[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	VECTOR result;
	tVec[0] = vec.x;
	tVec[1] = vec.y;
	tVec[2] = vec.z;
	tVec[3] = 1;
	for(int i = 0; i < 4; i++)
	{
		for(int k = 0; k < 4; k++)
		{
			rVec[i] += (mat.m[i][k] * tVec[k]);
		}
	}

	result.x = rVec[0];
	result.y = rVec[1];
	result.z = rVec[2];

	return result;
}

float GetAngleX(VECTOR vec1, VECTOR vec2)
{//角度を取得（X軸）
	return -(atan2f( vec1.y - vec2.y, vec1.z - vec2.z ));
}

float GetAngleY(VECTOR vec1, VECTOR vec2)
{//角度を取得（Y軸）
	return atan2f( vec1.x - vec2.x, vec1.z - vec2.z );
}

float GetAngleZ(VECTOR vec1, VECTOR vec2)
{//角度を取得（Z軸）
	return -(atan2f( vec1.y - vec2.y, vec1.x - vec2.x ));
}

float MyAbsf(float i_fNum)
{//絶対値の取得
	if(i_fNum < 0.0f)
	{
		i_fNum = -i_fNum;
	}
	return i_fNum;
}

MATRIX GetIdentityMatrix()
{//単位行列を取得する
	MATRIX test;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
			{
				test.m[i][j] = 1;
			}
			else
			{
				test.m[i][j] = 0;
			}
		}
	}
	return test;
}

MATRIX GetTranslateMatrix(float x, float y, float z)
{// 平行移動行列を取得する
	MATRIX test = GetIdentityMatrix();
	test.m[0][3] = x;
	test.m[1][3] = y;
	test.m[2][3] = z;

	return test;
}

MATRIX GetScaleMtrix(VECTOR SCALE)
{
	MATRIX test = GetIdentityMatrix();
	test.m[0][0] = SCALE.x;
	test.m[1][1] = SCALE.y;
	test.m[2][2] = SCALE.z;

	return test;
}

MATRIX GetPitchMatrix(float Rad)
{
	MATRIX test = GetIdentityMatrix();
	test.m[1][1] = cosf(Rad);
	test.m[1][2] = -sinf(Rad);
	test.m[2][1] = sinf(Rad);
	test.m[2][2] = cosf(Rad);

	return test;
}

MATRIX GetYawMatrix(float Rad)
{
	MATRIX test = GetIdentityMatrix();
	test.m[0][0] = cosf(Rad);
	test.m[0][2] = sinf(Rad);
	test.m[2][0] -= sinf(Rad);
	test.m[2][2] = cosf(Rad);

	return test;
}

MATRIX GetRollMatrix(float Rad)
{
	MATRIX test = GetIdentityMatrix();
	test.m[0][0] = cosf(Rad);
	test.m[0][1] -= sinf(Rad);
	test.m[1][0] = sinf(Rad);
	test.m[1][1] = cosf(Rad);

	return test;
}

MATRIX MatAdd(MATRIX matA, MATRIX matB)
{
	MATRIX test = { 0 };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			test.m[i][j] = matA.m[i][j] + matB.m[i][j];
		}
	}
	return test;
}

MATRIX MatScale(MATRIX matA, float scale)
{
	MATRIX test = { 0 };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			test.m[i][j] = matA.m[i][j] * scale;
		}
	}
	return test;
}

MATRIX MatMult(MATRIX matA, MATRIX matB)
{
	MATRIX test = { 0 };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				test.m[i][j] += (matA.m[i][k] * matB.m[k][j]);
			}
		}
	}
	return test;
}

VECTOR MatTransform(MATRIX matA, VECTOR vec1)
{
	float test[4] = { 0 };
	float result_buf[4] = { 0 };
	VECTOR result_vec;
	test[0] = vec1.x;
	test[1] = vec1.y;
	test[2] = vec1.z;
	test[3] = 1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result_buf[i] += (matA.m[i][j] * test[j]);
		}
	}

	result_vec.x = result_buf[0];
	result_vec.y = result_buf[1];
	result_vec.z = result_buf[2];

	return result_vec;
}

MATRIX MatTranspose(MATRIX mat)
{
	MATRIX result = { 0 };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[j][i] = mat.m[i][j];
		}
	}

	return result;
}

// ディグリー角をラジアン角に
float DegRad(float deg) {
	return deg * (DX_PI_F / 180);
}