#include "DxLib.h"

#include "game.h"
#include"SceneMain.h"
#include"SceneTitle.h"


SceneTitle::SceneTitle()
{

}

SceneTitle::~SceneTitle()
{

}

void SceneTitle::init()
{

}

void SceneTitle::end()
{
	
}

// ゲーム処理
void SceneTitle::update()
{

}

// 描画
void SceneTitle::draw()
{
	DrawString(0, 0, "SceneTitleの表示", GetColor(255, 255, 255));
}

