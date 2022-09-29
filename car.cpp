#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	// 待ち時間
	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 180;
	// 車の速度
	constexpr float kSpeed = -12.0f;
	// 車のジャンプ力
	constexpr float CarJump = -18.0f;
	// 車の重力
	constexpr float CarGrabity = 1.0f;
	// 車の飛ぶ位置
	constexpr int CarJumpPlace = 480;
	// 車の止まる位置
	constexpr int CarStop = 480;
}

Car::Car()
{
//	GetRand(100);//0~100

	m_handle = -1;
	m_fieldY = 0.0f;
	m_moveType = kMoveTypeNormal;
	m_waitFrame = 0;
	m_waitTime = 60;
}

void Car::setGraphic(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_size.x, &m_size.y);
}

void Car::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = Game::kScreenWidth + 16.0f;
	m_pos.y = m_fieldY - m_size.y;

	m_vec.x = kSpeed;
	m_vec.y = 0.0f;

	// 動きのバリエーションを追加
	int randNum = GetRand(99);
	if (randNum < 37)
	{
		m_moveType = kMoveTypeNormal;
	}
	else if (randNum < 37 + 30)
	{
		m_moveType = kMoveTypeStop;
	}
	else if (randNum < 37 + 30 + 30)
	{
		m_moveType = kMoveTypeJump;
	}
	else if (randNum < 37 + 30 + 30 + 1)
	{
		m_moveType = kMoveTypeFeint;
	}
	else
	{
		m_moveType = kMoveTypeReturn;
	}
	// デバック用に挙動を決める
	// m_moveType = kMoveTypeReturn;


	// 動き始めるまでの時間を設定	1秒から3秒待つ	60フレームから180フレーム
	m_waitFrame = GetRand(kWaitFrameMax - kWaitFrameMin) + kWaitFrameMin;
}

void Car::update()
{
	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		return;
	}

	switch (m_moveType)
	{
	case Car::kMoveTypeNormal:
		updateNormal();
		break;
	case Car::kMoveTypeStop:
		updateStop();
		break;
	case Car::kMoveTypeJump:
		updateJump();
		break;
	case Car::kMoveTypeReturn:
		updateReturn();
		break;
	case Car::kMoveTypeFeint:
		updateFeint();
		break;
	default:
		updateNormal();
		break;
	}
	
	updateNormal();
}

void Car::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	//DrawFormatString(0,0,GetColor(255,255,255),"wait:%d",m_waitFrame);
}

///////////////////////////////////////////////////////////
//private
///////////////////////////////////////////////////////////

// まっすぐ進む
void Car::updateNormal()
{
	m_pos += m_vec;
}

// 一時停止フェイント
void Car::updateStop()
{
	m_pos += m_vec;// 仮
	
	if (m_pos.x < CarStop)
	{
		m_vec.x = 0.0f;
		m_waitTime--;
	}
	if (m_waitTime < 0)
	{
		m_vec.x = kSpeed;
	}
	
}

// ジャンプする
void Car::updateJump()
{
	m_pos += m_vec;// 仮
	// 地面とのあたり
	bool isFieldC = false;
	if (m_pos.y > m_fieldY - m_size.y)
	{
		m_pos.y = m_fieldY - m_size.y;
		isFieldC = true;
	}
	if (m_pos.x < CarJumpPlace)
	{
		if (isFieldC)
		{
			m_vec.y = CarJump;	// ジャンプ処理
		}
	}
	m_vec.y += CarGrabity;
}

// 一時停止フェイント
void Car::updateFeint()
{
	m_pos += m_vec;// 仮

	if (m_pos.x < 500)
	{
		m_vec.x = -0.1f;
	}
	if (m_pos.x < 450)
	{
		m_vec.x = kSpeed;
	}

}


// 途中で引き返す(絶対成功)
void Car::updateReturn()
{
	m_pos += m_vec;// 仮

	if (m_pos.x < 320)
	{
		m_vec.x = kSpeed*-1;
	}
	
}