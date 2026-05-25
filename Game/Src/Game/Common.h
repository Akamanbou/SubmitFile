#pragma once
#include<DxLib.h>
#include<math.h>

static const int  WINDOW_SIZE_X = 1280; // 画面サイズX
static const int WINDOW_SIZE_Y = 640;  // 画面サイズY
static const VECTOR ZERO = { 0.0f,0.0f,0.0f }; // VECTOR型のゼロ
static const float GRAVITY = 0.1f; // 重力

static const int BAR_LEFT = 380;
static const int BAR_RIGHT = 900;
static const int BAR_TOP = 630;
static const int BAR_BOTTOM = 650;

static const int RED = GetColor(255, 0, 0);
static const int GREEN = GetColor(0, 255, 0);
static const int BLUE = GetColor(0, 0, 255);
static const int YELLOW = GetColor(255, 200, 0);
static const int WHITE = GetColor(255, 255, 255);

static const float RAD = DX_PI_F / 180; // ラジアン角に直すとき
static const float DIG = 180 / DX_PI_F; // ディグリー角に直すとき