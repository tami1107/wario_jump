#pragma once

#include "car.h"
#include "player.h"

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	// �����������A�I������
	void init();
	void end();

	// �Q�[������
	void update();
	// �`�揈��
	void draw();
private:
	// �O���t�B�b�N�n���h��
	int m_hPlayer;
	int m_hCar;

	// �v���C���[
	Player m_player;
	// �G
	Car m_car;

};
