#pragma once

#include "car.h"
#include "player.h"
class SceneTitle
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	// �����������A�I������
	void init();
	void end();

	// �Q�[������
	void update();
	// �`�揈��
	void draw();

};
