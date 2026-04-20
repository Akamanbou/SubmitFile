#ifndef _MYMATH_H_
#define _MYMATH_H_

#include "DxLib.h"

//ベクトルや行列の計算処理をまとめたクラス
VECTOR VecCreate(VECTOR PosA, VECTOR PosB);//ベクトル作成
float VecLong(VECTOR PosA, VECTOR PosB);//ベクトルの長さ
VECTOR VecAdd(VECTOR vecA, VECTOR vecB);//ベクトルの足し算
VECTOR VecSubtract(VECTOR vecA, VECTOR vecB);//ベクトルの引き算
VECTOR VecScale(VECTOR vec, float scale);//ベクトルのスカラー倍
float VecDot(VECTOR vecA, VECTOR vecB);//ベクトルの内積
VECTOR VecCross(VECTOR vecA, VECTOR vecB);//ベクトルの外積
VECTOR VecNormalize(VECTOR vec);//ベクトルの正規化
void Matldentity(MATRIX *mp);//単位行列の取得
//MATRIX MatAdd(MATRIX matA, MATRIX matB);//行列の足し算
MATRIX MyMatMult(MATRIX matA, MATRIX matB);//行列の掛け算
//MATRIX MatScale(MATRIX mat, float scale);//行列のスカラー倍
VECTOR Transform(MATRIX mat, VECTOR vec);//ベクトル×行列
float GetAngleY(VECTOR vec1, VECTOR vec2);//角度を取得(Y軸)
float GetAngleX(VECTOR vec1, VECTOR vec2);//角度を取得(X軸)
float GetAngleZ(VECTOR vec1, VECTOR vec2);//角度を取得(Z軸)
float MyAbsf(float i_fNum);//絶対値の取得
#endif
MATRIX GetIdentityMatrix();
MATRIX GetTranslateMatrix(float x, float y, float z);
MATRIX GetScaleMtrix(VECTOR SCALE);
MATRIX GetPitchMatrix(float Rad);
MATRIX GetYawMatrix(float Rad);
MATRIX GetRollMatrix(float Rad);
MATRIX MatAdd(MATRIX matA, MATRIX matB);
MATRIX MatScale(MATRIX matA, float scale);
MATRIX MatMult(MATRIX matA, MATRIX matB);
VECTOR MatTransform(MATRIX matA, VECTOR vec1);
MATRIX MatTranspose(MATRIX mat);
float DegRad(float deg);