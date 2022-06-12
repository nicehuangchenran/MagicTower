#include "Headers.h"
#include "Scene/HelloWorldScene.h"

Hero::Hero() {}

Hero::~Hero() {}

Hero* Hero::create(test_start* scene, Vec2 tilePosition)
{
	Hero* heroPointer = new Hero;

	//异常处理
	if (heroPointer && heroPointer->init(scene, tilePosition))
	{
		heroPointer->autorelease();
		sGlobal->hero = heroPointer;
		return heroPointer;
	}
	else
	{
		return nullptr;
	}
}

bool Hero::init(test_start* scene, Vec2 tilePosition)
{
	//调用父类初始化函数
	if (!Node::init())
	{
		return false;
	}

	//初始化状态数据
	targetTilePosition = tilePosition;
	targetGLPosition = sGlobal -> gameMap -> positionForTileCoord(tilePosition);
	isStopping = true;
	if (sGlobal->hero)
	{
		*this = *sGlobal->hero;
	}
	else
	{
		blood = INIT_BLOOD;
		atk = INIT_ATK;
		def = INIT_DEF;
		gold = INIT_GOLD;
		key[YELLOW] = 1;
		key[BLUE] = 0;
		key[RED] = 0;
		sword = "无";
		shield = "无";
	}

	//战斗界面
	fightLayer = new FightLayer;

	//绑定场景
	this->scene = scene;

	//设置精灵
	image = Sprite::create("img/1.png", Rect(0, OBJECT_SIZE * 10 + 1, OBJECT_SIZE, OBJECT_SIZE));//创建精灵
	image->setAnchorPoint(Point::ZERO);//设置锚点为左下角
	this->addChild(image);//绑定精灵

	return true;
}

//移动一格
void Hero::move(EventKeyboard::KeyCode code)
{
	//如果上一个move函数还在执行，则不继续执行
	if (!isStopping)
	{
		return;
	}

	//确定移动的距离
	Point moveDist;
	switch (code)
	{
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			faceDirection = UP;
			moveDist = Point(0, OBJECT_SIZE);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			faceDirection = DOWN;
			moveDist = Point(0, -OBJECT_SIZE);
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			faceDirection = LEFT;
			moveDist = Point(-OBJECT_SIZE, 0);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			faceDirection = RIGHT;
			moveDist = Point(OBJECT_SIZE, 0);
			break;
		default:
			return;
	}

	//计算目标位置
	targetGLPosition = this->getPosition() + moveDist;
	targetGLPosition.x -= 160;  //将GL坐标系原点设为(160,0)，待用函数封装

	//测试坐标
	//log("%f, %f", sGlobal->gameMap->getMapSize().width, sGlobal->gameMap->getMapSize().height);
	
	//碰撞检测
	COLLISION_TYPE colli = collisionCheck(targetGLPosition);
	if (colli == COLLI_WALL || colli == COLLI_ENEMY || colli == COLLI_DOOR || colli == COLLI_NPC)
	{
		//脸部方向改变，绘制新图
		this->image->setTextureRect(Rect(0, OBJECT_SIZE * faceDirection + 1, OBJECT_SIZE, OBJECT_SIZE));
		return;
	}
	
	//行走动画
	walkAnimation(faceDirection);

	//脸部方向改变，绘制新图
	this->image->setTextureRect(Rect(0, OBJECT_SIZE * faceDirection + 1, OBJECT_SIZE, OBJECT_SIZE));

	//移动到新位置
	Action* action = Sequence::create(
		MoveBy::create(0.20f, moveDist),
		CallFuncN::create(CC_CALLBACK_1(Hero::moveIsDone, this)),
		NULL);
	this->runAction(action);

	isStopping = false;
}

void Hero::moveIsDone(Node* node)
{
	isStopping = true;
}

void Hero::walkAnimation(int faceDirection)
{
	auto heroTexture = Director::getInstance()->getTextureCache()->addImage("img/1.png");

	auto frame0 = SpriteFrame::createWithTexture(heroTexture,
		Rect(OBJECT_SIZE * 0, OBJECT_SIZE * faceDirection, OBJECT_SIZE, OBJECT_SIZE));
	auto frame1 = SpriteFrame::createWithTexture(heroTexture,
		Rect(OBJECT_SIZE * 1, OBJECT_SIZE * faceDirection, OBJECT_SIZE, OBJECT_SIZE));
	auto frame2 = SpriteFrame::createWithTexture(heroTexture,
		Rect(OBJECT_SIZE * 2, OBJECT_SIZE * faceDirection, OBJECT_SIZE, OBJECT_SIZE));
	auto frame3 = SpriteFrame::createWithTexture(heroTexture,
		Rect(OBJECT_SIZE * 3, OBJECT_SIZE * faceDirection, OBJECT_SIZE, OBJECT_SIZE));
	Vector<SpriteFrame*> animFrames;
	animFrames.pushBack(frame0);
	animFrames.pushBack(frame1);
	animFrames.pushBack(frame2);
	animFrames.pushBack(frame3);
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
	image->runAction(Repeat::create(Animate::create(animation), 1));
}

COLLISION_TYPE Hero::collisionCheck(Vec2 targetGLPosition)
{
	targetTilePosition = sGlobal -> gameMap -> tileCoordForPosition(targetGLPosition);
	//地图边界
	
	if (targetTilePosition.x < 0 ||
		targetTilePosition.y < 0 ||
		targetTilePosition.x > sGlobal->gameMap->getMapSize().width - 1 ||
		targetTilePosition.y > sGlobal->gameMap->getMapSize().height - 1)
	{
		return COLLI_WALL;
	}

	//对应图块是地图内的墙
	targetTileGID = sGlobal->gameMap->getWallLayer()->getTileGIDAt(targetTilePosition);
	if (targetTileGID)
	{
		return COLLI_WALL;
	}
	
	//对应图块是怪物
	targetTileGID = sGlobal->gameMap->getEnemyLayer()->getTileGIDAt(targetTilePosition);
	if (targetTileGID)
	{ 
		this->fightWithEnemy(targetTileGID, targetTilePosition);
		return COLLI_ENEMY; 
	}
	
	//对应图块是道具
	targetTileGID = sGlobal->gameMap->getItemLayer()->getTileGIDAt(targetTilePosition);
	if (targetTileGID)
	{
		//得到道具
		getItem(targetTileGID);  

		//删除道具
		sGlobal->gameMap->getItemLayer()->removeTileAt(targetTilePosition);  

		return COLLI_ITEM;
	}

	//对应图块是门
	targetTileGID = sGlobal->gameMap->getDoorLayer()->getTileGIDAt(targetTilePosition);
	if (targetTileGID)
	{
		int color = (targetTileGID - 120) / 24; //计算门的颜色
		if (key[color])
		{
			openDoor(targetTileGID, color);
		}
		else
		{
			sGlobal->gameMap->showInfo("No Key!", 500);
		}
		
		return COLLI_DOOR;
	}
	int index = targetTilePosition.x + targetTilePosition.y * sGlobal->gameMap->getMapSize().width;

	//对应图块是NPC
	auto npc = sGlobal->gameMap->npcDict.at(index);
	if (npc != NULL)
	{
		npcTalk(npc->getNPCID());
		return COLLI_NPC;
	}

	//对应图块是传送门（楼梯）
	auto teleport = sGlobal->gameMap->teleportDict.at(index);
	if (teleport != NULL)
	{
		teleTransport(teleport);
		return COLLI_TELEPORT;
	}

	return COLLI_NONE;
}


void Hero::npcTalk(const int npcID)
{
	switch (npcID) {
		case 1:
			sGlobal->gameMap->showTip("勇士\n欢迎来到魔塔\n");
			break;
		case 2:
			sGlobal->gameMap->showTip("感谢你救我出来\n，这500元请收下");
			break;
		case 3:
			sGlobal->gameMap->showTip("告诉你\n这个塔有12层");
			break;
		case 4:
			sGlobal->gameMap->showTip("下面的路要小心");
			break;
		case 5:
			sGlobal->gameMap->showTip("好久没有在这一层看到人了");
			break;
		case 6:
			sGlobal->gameMap->showTip("加油，我的勇士");
			break;
	}
}

void Hero::teleTransport(Teleport* teleport)
{	
	// 获取目标层数与英雄位置，然后切换场景
	sGlobal->currentLevel = teleport->targetID;
	sGlobal->heroSpawnTileCoord = teleport->targetHeroPosition;
	Director::getInstance()->replaceScene(TransitionFadeTR::create(0.5f, sGlobal -> test_start -> createScene()));
}

void Hero::getItem(const int gid)
{
	//CCLOG("%d", gid);
		if (gid >= 1 && gid <= 3)
	{
		getKey(ITEM_COLOR(gid - 1));
	}
	else if (gid == 27 || gid == 28)
	{
		getPotion(ITEM_COLOR(29 - gid));
	}
	else if (gid == 25 || gid == 26)
	{
		getGem(ITEM_COLOR(27 - gid));
	}
	else if (gid >= 72 && gid <= 76)
	{
		getSword(WEAPON_TYPE(gid - 72));
	}
	else if (gid >= 96 && gid <= 100)
	{
		getShield(WEAPON_TYPE(gid - 96));
	}

}

void Hero::getKey(const ITEM_COLOR color)
{
	//如果音效开启，则播放音效
	if (Setting::isEffect)	SimpleAudioEngine::getInstance()->playEffect("gameEffect/getItem.mp3");

	sGlobal->gameMap->showTip("获得钥匙");
	this->key[color]++;
}

void Hero::getPotion(const ITEM_COLOR color)
{
	//如果音效开启，则播放音效
	if (Setting::isEffect)	SimpleAudioEngine::getInstance()->playEffect("gameEffect/getBlood.mp3");

	int addBlood = 0;
	switch (color)
	{
		case RED:
			addBlood = 50 * (sGlobal->currentLevel / 10 + 1);
			break;
		case BLUE:
			addBlood = 200 * (sGlobal->currentLevel / 10 + 1);
			break;
	}
	sGlobal->gameMap->showTip(("血量+" + Value(addBlood).asString()).data());
	this->blood += addBlood;
}

//获得宝石
void Hero::getGem(const ITEM_COLOR color)
{
	//如果音效开启，则播放音效
	if (Setting::isEffect)	SimpleAudioEngine::getInstance()->playEffect("gameEffect/getItem.mp3");

	switch (color)
	{
		case RED:
			this->atk += sGlobal->currentLevel / 10 + 1;
			sGlobal->gameMap->showTip(("攻击+" + Value(sGlobal->currentLevel / 10 + 1).asString()).data());
			break;
		case BLUE:
			this->def += sGlobal->currentLevel / 10 + 1;
			sGlobal->gameMap->showTip(("防御+" + Value(sGlobal->currentLevel / 10 + 1).asString()).data());
			break;
	}
}

//获得剑
void Hero::getSword(const WEAPON_TYPE type)
{
	//如果音效开启，则播放音效
	if (Setting::isEffect)	SimpleAudioEngine::getInstance()->playEffect("gameEffect/getItem.mp3");

	int addAtk = 0;
	switch (type)
	{
		case IRON:
			addAtk = 10;
			sword = "铁剑";
			break;
		case SLIVER:
			addAtk = 20;
			sword = "银剑";
			break;
		case KNIGHT:
			addAtk = 40;
			sword = "骑士剑";
			break;
		case HOLY:
			addAtk = 50;
			sword = "神圣剑";
			break;
	}
	sGlobal->gameMap->showTip(("获得"+sword+"\n攻击+" + Value(addAtk).asString()).data());
	this->atk += addAtk;
}

//获得盾
void Hero::getShield(const WEAPON_TYPE type)
{
	//如果音效开启，则播放音效
	if (Setting::isEffect)	SimpleAudioEngine::getInstance()->playEffect("gameEffect/getItem.mp3");

	int addDef = 0;
	switch (type)
	{
		case IRON:
			addDef = 10;
			sword = "铁盾";
			break;
		case SLIVER:
			addDef = 20;
			sword = "银盾";
			break;
		case KNIGHT:
			addDef = 40;
			sword = "骑士盾";
			break;
		case HOLY:
			addDef = 50;
			sword = "神圣盾";
			break;
	}
	sGlobal->gameMap->showTip(("获得" + shield + "\n防御+" + Value(addDef).asString()).data());
	this->def += addDef;
}

void Hero::fightWithEnemy(const int enemyID, Vec2 targetTilePosition)
{
	//检查怪物ID是否正确
	if (enemyID < 1 || enemyID > GID_MAX)
	{
		return;
	}

	//禁用其他动作
	isStopping = false;

	//获取怪物信息
	auto enemy = new Enemy; //在fightLayer->fight()里delete
	*enemy = sGlobal->enemyMap[enemyID];

	//初始化显示
	scene->addChild(fightLayer); //fightLayer不能作为hero的child
	fightLayer->initDisplay(this, enemy);

	//进行回合制战斗
	fightLayer->fight(scene, this, enemy, targetTilePosition);
}

int Hero::bldNum()
{
	return blood;
}

int Hero::atkNum()
{
	return atk;
}

int Hero::defNum()
{
	return def;
}

int Hero::mnyNum()
{
	return gold;
}

int Hero::keyNum(const int color)
{
	return key[color];
}

std::string Hero::swordName()
{
	return sword;
}

std::string Hero::shieldName()
{
	return shield;
}

void Hero::openDoor(const int gid, const int color)
{
	//如果音效开启，则播放音效
	if (Setting::isEffect)	SimpleAudioEngine::getInstance()->playEffect("gameEffect/openDoor.mp3");

	//禁止其他动作
	isStopping = false;

	//消耗钥匙
	key[color]--;

	//保存正在被开启的门的初始GID
	targetDoorGID = gid;

	//定时器更新门动画
	schedule(schedule_selector(Hero::updateOpenDoorAnimation), 0.1f);
}

void Hero::updateOpenDoorAnimation(float time)
{
	//计算动画下一帧的图块ID，TileMap的图块编号方式是横向递增1，所以每列相同的位置的图块ID相差了每行图块的个数
	int nextGID = sGlobal->gameMap->getDoorLayer()->getTileGIDAt(targetTilePosition) + 1;

	//如果超过了第四帧动画，就将当前位置的图块删除，并取消定时器
	if (nextGID - targetDoorGID >= 4)
	{
		sGlobal->gameMap->getDoorLayer()->removeTileAt(targetTilePosition); //删除门
		unschedule(schedule_selector(Hero::updateOpenDoorAnimation)); //取消定时器
		isStopping = true; //状态恢复
	}
	else
	{
		//更新动画至下一帧
		sGlobal->gameMap->getDoorLayer()->setTileGID(nextGID, targetTilePosition);
	}
}