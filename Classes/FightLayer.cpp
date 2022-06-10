#include "Headers.h"

FightLayer::FightLayer() {}

FightLayer::~FightLayer(){}

void FightLayer::initDisplay(const Hero* const hero, const Enemy* const enemy)
{
	//创建战斗界面
	fightWindow = Sprite::create("img/6.jpg");
	fightWindow->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2)); //显示在屏幕正中
	this->addChild(fightWindow);

	//显示战斗双方图标
	this->heroSprite = Sprite::create("img/1.png", Rect(0, OBJECT_SIZE * 10, OBJECT_SIZE, OBJECT_SIZE));
	this->heroSprite->setPosition(Vec2(300, 240));
	this->enemySprite = Sprite::create("img/1.png", Rect(enemy->graphPosition.x * OBJECT_SIZE, enemy->graphPosition.y * OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE));
	this->enemySprite->setPosition(Vec2(450, 240));
	this->addChild(heroSprite);
	this->addChild(enemySprite);

	//显示数值信息
	this->heroInfo = "血量：" + Value(hero->blood).asString() + "\n"
		+ "攻击：" + Value(hero->atk).asString() + "\n"
		+ "防御：" + Value(hero->def).asString();
	this->enemyInfo = "血量：" + Value(enemy->blood).asString() + "\n"
		+ "攻击：" + Value(enemy->atk).asString() + "\n"
		+ "防御：" + Value(enemy->def).asString();
	this->heroLabel = Label::create(heroInfo, "arial", 16);
	this->heroLabel->setColor(Color3B(0, 0, 0));
	this->heroLabel->setAnchorPoint(Vec2(0, 1));
	this->heroLabel->setPosition(Vec2(252, 210));
	this->addChild(heroLabel);
	this->enemyLabel = Label::create(enemyInfo, "arial", 16);
	this->enemyLabel->setColor(Color3B(0, 0, 0));
	this->enemyLabel->setAnchorPoint(Vec2(0, 1));
	this->enemyLabel->setPosition(Vec2(400, 210));
	this->addChild(enemyLabel);
}

void FightLayer::fight(test_start* scene, Hero* hero, Enemy* enemy, Vec2 targetTilePosition)
{
	this->schedule([=](float dlt)
		{
			//当英雄血量或怪物血量为0时结束战斗
			if (hero->blood == 0 || enemy->blood == 0)
			{
				//关闭界面
				this->removeChild(heroSprite);
				this->removeChild(enemySprite);
				this->removeChild(heroLabel);
				this->removeChild(enemyLabel);
				this->removeChild(fightWindow);
				scene->removeChild(this);

				//停止计时器
				this->unschedule("fight");

				//状态恢复
				hero->isStopping = true;

				//更新信息显示
				scene->flushHeroProperties();

				if (hero->blood) //战胜
				{
					//获得金币
					hero->gold += enemy->gold;

					//怪物图片消失
					sGlobal->gameMap->getEnemyLayer()->removeTileAt(targetTilePosition);
				}
				else //战败，游戏结束
				{

				}

				//释放空间
				delete enemy;
			}
			else
			{
				//计算血量
				if (whoseTurn) //怪物的回合
				{
					//根据怪物类型计算伤害
					int loseBlood = 0;
					switch (enemy->type)
					{
						case ENEMY_TYPE_NORMAL:
							loseBlood = enemy->atk - hero->def;
							if (loseBlood < 0) loseBlood = 0;
							break;
						case ENEMY_TYPE_CRITICAL:
							loseBlood = enemy->atk * (1 + (rand() % 2) * 0.5) - hero->def;
							if (loseBlood < 0) loseBlood = 0;
							break;
						case ENEMY_TYPE_BOSS:
							loseBlood = enemy->atk;
							break;
					}

					//造成伤害
					hero->blood -= loseBlood;
					if (hero->blood < 0) hero->blood = 0;
				}
				else //英雄的回合
				{
					//计算伤害
					int loseBlood = hero->atk - enemy->def;
					if (loseBlood < 0) loseBlood = 0;

					//造成伤害
					enemy->blood -= loseBlood;
					if (enemy->blood < 0) enemy->blood = 0;
				}
				whoseTurn ^= 1; //回合交换

				//显示新的战斗信息
				heroInfo = "血量：" + Value(hero->blood).asString() + "\n"
					+ "攻击：" + Value(hero->atk).asString() + "\n"
					+ "防御：" + Value(hero->def).asString();
				heroLabel->setString(heroInfo);
				enemyInfo = "血量：" + Value(enemy->blood).asString() + "\n"
					+ "攻击：" + Value(enemy->atk).asString() + "\n"
					+ "防御：" + Value(enemy->def).asString();
				enemyLabel->setString(enemyInfo);
			}
		}, 0.7f, "fight");
}