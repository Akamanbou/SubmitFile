
#ifndef __INPUT_H__
#define __INPUT_H__

//判定用ビット
#define KEY_Z		(1 << 0)	// Zキー
#define KEY_UP    (1 << 1)	// カメラのX軸回転上
#define KEY_DOWN (1 << 2)	// カメラのX軸回転下
#define MOUSE_LEFT (1<<3)
#define KEY_R (1<<4)
#define MOUSE_RIGHT (1<<5)
#define KEY_SPACE (1<<6)
#define KEY_E (1<<7)
#define KEY_W (1<<8)
#define KEY_A (1<<9)
#define KEY_S (1<<10)
#define KEY_D (1<<11)
#define KEY_F (1<<12)


class CInput {
public:
	//入力制御初期化
	static void InitInput();

	//入力制御ステップ
	//StepInputは他のStepより早く呼ぶ
	static void StepInput();

	//今押された
	static bool IsPush(int key_bit);

	//押されている
	static bool IsCont(int key_bit);

	// 今離した
	static bool Release(int key_bit);
	
private:
	static int pre_key_state;		//前回のキー状態
	static int current_key_state;	//今回のキー状態
};

#endif

