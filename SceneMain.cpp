#include "DxLib.h"

#include "game.h"
#include"SceneMain.h"

namespace
{
	// 地面の高さ
	constexpr int kFieldY = Game::kScreenHeight - 64;
}

SceneMain::SceneMain()
{

}

SceneMain::~SceneMain()
{

}

void SceneMain::init()
{
	m_hPlayer = LoadGraph("data/player.png");
	m_hCar = LoadGraph("data/car.png");

	m_player.setGraphic(m_hPlayer);
	m_player.setup(kFieldY);

	m_car.setGraphic(m_hCar);
	m_car.setup(kFieldY);
}

void SceneMain::end()
{
	DeleteGraph(m_hPlayer);
	DeleteGraph(m_hCar);
}

// ゲーム処理
void SceneMain::update()
{
	m_player.update();
	m_car.update();

	// 当たり判定
	if (m_player.isCol(m_car))
	{
		m_player.setDead(true);
	}
}

// 描画
void SceneMain::draw()
{
	// 地面の描画
	DrawLine(0, kFieldY, Game::kScreenWidth, kFieldY, GetColor(255, 255, 255));
	m_player.draw();
	m_car.draw();
}

