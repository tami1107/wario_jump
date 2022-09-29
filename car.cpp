#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	// �҂�����
	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 180;
	// �Ԃ̑��x
	constexpr float kSpeed = -12.0f;
	// �Ԃ̃W�����v��
	constexpr float CarJump = -18.0f;
	// �Ԃ̏d��
	constexpr float CarGrabity = 1.0f;
	// �Ԃ̔�Ԉʒu
	constexpr int CarJumpPlace = 480;
	// �Ԃ̎~�܂�ʒu
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

	// �����̃o���G�[�V������ǉ�
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
	// �f�o�b�N�p�ɋ��������߂�
	// m_moveType = kMoveTypeReturn;


	// �����n�߂�܂ł̎��Ԃ�ݒ�	1�b����3�b�҂�	60�t���[������180�t���[��
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

// �܂������i��
void Car::updateNormal()
{
	m_pos += m_vec;
}

// �ꎞ��~�t�F�C���g
void Car::updateStop()
{
	m_pos += m_vec;// ��
	
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

// �W�����v����
void Car::updateJump()
{
	m_pos += m_vec;// ��
	// �n�ʂƂ̂�����
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
			m_vec.y = CarJump;	// �W�����v����
		}
	}
	m_vec.y += CarGrabity;
}

// �ꎞ��~�t�F�C���g
void Car::updateFeint()
{
	m_pos += m_vec;// ��

	if (m_pos.x < 500)
	{
		m_vec.x = -0.1f;
	}
	if (m_pos.x < 450)
	{
		m_vec.x = kSpeed;
	}

}


// �r���ň����Ԃ�(��ΐ���)
void Car::updateReturn()
{
	m_pos += m_vec;// ��

	if (m_pos.x < 320)
	{
		m_vec.x = kSpeed*-1;
	}
	
}