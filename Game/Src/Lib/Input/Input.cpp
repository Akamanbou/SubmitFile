
#include "DxLib.h"
#include "Input.h"

int CInput::pre_key_state = 0;		//前回のキー状態
int CInput::current_key_state = 0;	//今回のキー状態

//入力制御初期化
void CInput::InitInput()
{
	pre_key_state = 0;
	current_key_state = 0;
}

//入力制御ステップ
void CInput::StepInput()
{
	//前回のキー状態を保存
	pre_key_state = current_key_state;

	//今回のキー状態を判定前にfalseに
	current_key_state = 0;

	//必要なキーは以下に判定を書く

	if(CheckHitKey(KEY_INPUT_Z) == 1)
		current_key_state |= KEY_Z;
	if (CheckHitKey(KEY_INPUT_UP) == 1)
		current_key_state |= KEY_UP;
	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
		current_key_state |= KEY_DOWN;
	if ((GetMouseInput() & MOUSE_INPUT_LEFT)!=0)
		current_key_state |= MOUSE_LEFT;
	if (CheckHitKey(KEY_INPUT_R) == 1)
		current_key_state |= KEY_R;
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT)!=0)
		current_key_state |= MOUSE_RIGHT;
	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		current_key_state |= KEY_SPACE;
	if (CheckHitKey(KEY_INPUT_E) == 1)
		current_key_state |= KEY_E;
	if (CheckHitKey(KEY_INPUT_W) == 1)
		current_key_state |= KEY_W;
	if (CheckHitKey(KEY_INPUT_A) == 1)
		current_key_state |= KEY_A;
	if (CheckHitKey(KEY_INPUT_S) == 1)
		current_key_state |= KEY_S;
	if (CheckHitKey(KEY_INPUT_D) == 1)
		current_key_state |= KEY_D;
	if (CheckHitKey(KEY_INPUT_F) == 1)
		current_key_state |= KEY_F;



}

//今押された
bool CInput::IsPush(int key_bit)
{
	if((current_key_state & key_bit) && (pre_key_state & key_bit) == false)
		return true;

	return false;
}

//押されている
bool CInput::IsCont(int key_bit)
{
	if(current_key_state & key_bit)
		return true;

	return false;
}

// 今離された
bool CInput::Release(int key_bit)
{
	if ((pre_key_state & key_bit) && (current_key_state & key_bit) == false)
	{
		return true;
	}
	return false;
}

