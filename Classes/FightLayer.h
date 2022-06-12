#ifndef _FIGHT_LAYER_H_
#define _FIGHT_LAYER_H_

#include "cocos2d.h"
#include "Entity/Hero.h"
#include "Entity/Enemy.h"

class FightLayer : public Layer
{
public:
	FightLayer();
	~FightLayer();
	void initDisplay(const Hero* hero, const Enemy* enemy); //初始显示
	void fight(GameScene* scene, Hero* hero, Enemy* enemy, Vec2 targetTilePosition); //开始战斗过程
	void showLoseBlood(const int loseBlood, const ENEMY_TYPE type, const bool critical, const bool whoseTurn);

protected:
	std::string heroInfo; //英雄信息字符串
	std::string enemyInfo; //怪物信息字符串
	Label* heroLabel; //英雄标签
	Label* enemyLabel; //怪物标签
	Sprite* fightWindow; //战斗窗口
	Sprite* heroSprite; //英雄图标
	Sprite* enemySprite; //怪物图标
	bool whoseTurn; //0表示英雄的回合，1表示怪物的回合

};

#endif // !_FIGHT_LAYER_H_