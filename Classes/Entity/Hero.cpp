#include "Headers.h"

Hero::Hero() {}

Hero::~Hero()
{
	delete fightLayer;
}

//创建对象
Hero* Hero::create(test_start* scene, Vec2 tilePosition)
{
	//new申请空间
	static Hero* heroPointer = new Hero;

	//异常处理
	if (heroPointer && heroPointer->init(scene, tilePosition))
	{
		if (sGlobal->hero) //释放空间
		{
			delete sGlobal->hero;
		}
		sGlobal->hero = heroPointer;
		return heroPointer;
	}
	else
	{
		delete heroPointer;
		return nullptr;
	}
}

//初始化对象
bool Hero::init(test_start* scene, Vec2 tilePosition)
{
	//调用父类初始化函数
	if (!Node::init())
	{
		return false;
	}

	//初始化状态数据
	targetTilePosition = tilePosition;
	targetGLPosition = tilePosition * OBJECT_SIZE;
	blood = INIT_BLOOD;
	atk = INIT_ATK;
	def = INIT_DEF;
	gold = INIT_GOLD;
	key[ITEM_COLOR_YELLOW] = 1;
	key[ITEM_COLOR_BLUE] = 0;
	key[ITEM_COLOR_RED] = 0;
	sword = "无";
	shield = "无";
	isStopping = true;
	floor = 1;

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
			faceDirection = DIRECTION_UP;
			moveDist = Point(0, OBJECT_SIZE);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			faceDirection = DIRECTION_DOWN;
			moveDist = Point(0, -OBJECT_SIZE);
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			faceDirection = DIRECTION_LEFT;
			moveDist = Point(-OBJECT_SIZE, 0);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			faceDirection = DIRECTION_RIGHT;
			moveDist = Point(OBJECT_SIZE, 0);
			break;
		default:
			return;
	}

	//计算目标位置
	targetGLPosition = this->getPosition() + moveDist;
	targetGLPosition.x -= 160;  //将GL坐标系原点设为(160,0)，待用函数封装

	//测试坐标
	log("%f, %f", sGlobal->gameMap->getMapSize().width, sGlobal->gameMap->getMapSize().height);
	
	//碰撞检测
	CollisionType colli = collisionCheck(targetGLPosition);
	if (colli == kWall || colli == kEnemy || colli == kDoor || colli == kNPC)
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
		CallFuncN::create(CC_CALLBACK_1(Hero::moveIsDone, this, (void*)faceDirection)),
		NULL);
	this->runAction(action);

	isStopping = false;
}

void Hero::moveIsDone(Node* node, void* faceDirection)
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

CollisionType Hero::collisionCheck(Vec2 targetGLPosition)
{
	targetTilePosition = sGlobal -> gameMap -> tileCoordForPosition(targetGLPosition);
	//地图边界
	
	if (targetTilePosition.x < 0 ||
		targetTilePosition.y < 0 ||
		targetTilePosition.x > sGlobal->gameMap->getMapSize().width - 1 ||
		targetTilePosition.y > sGlobal->gameMap->getMapSize().height - 1)
	{
		return kWall;
	}

	//对应图块是地图内的墙
	targetTileGID = sGlobal->gameMap->getWallLayer()->getTileGIDAt(targetTilePosition);
	if (targetTileGID)
	{
		return kWall;
	}
	
	//对应图块是怪物
	targetTileGID = sGlobal->gameMap->getEnemyLayer()->getTileGIDAt(targetTilePosition);
	if (targetTileGID)
	{ 
		this->fightWithEnemy(targetTileGID, targetTilePosition);
		return kEnemy; 
	}
	
	//对应图块是道具
	targetTileGID = sGlobal->gameMap->getItemLayer()->getTileGIDAt(targetTilePosition);
	if (targetTileGID)
	{
		//得到道具
		getItem(targetTileGID);  

		//删除道具
		sGlobal->gameMap->getItemLayer()->removeTileAt(targetTilePosition);  

		return kItem;
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
		//...
		//删除门
		
		return kDoor;
	}


	return kNone;
}

void Hero::getItem(const int gid)
{
	CCLOG("%d", gid);
	if (gid >= 1 && gid <= 3)
	{
		getKey(gid - 1);
	}
	else if (gid == 27 || gid == 28)
	{
		getPotion(29 - gid);
	}
	else if (gid == 25 || gid == 26)
	{
		getGem(27 - gid);
	}
	else if (gid >= 72 && gid <= 76)
	{
		getSword(gid - 72);
	}
	else if (gid >= 96 && gid <= 100)
	{
		getShield(gid - 96);
	}
}

void Hero::getKey(const int color)
{
	sGlobal->gameMap->showTip("获得钥匙");
	this->key[color]++;
}

void Hero::getPotion(const int color)
{
	int addBlood = 0;
	switch (color)
	{
		case ITEM_COLOR_RED:
			addBlood = 50 * (floor / 10 + 1);
			break;
		case ITEM_COLOR_BLUE:
			addBlood = 200 * (floor / 10 + 1);
			break;
	}
	sGlobal->gameMap->showTip(("血量+" + Value(addBlood).asString()).data());
	this->blood += addBlood;
}

//获得宝石
void Hero::getGem(const int color)
{
	switch (color)
	{
		case ITEM_COLOR_RED:
			this->atk += floor / 10 + 1;
			sGlobal->gameMap->showTip(("攻击+" + Value(floor / 10 + 1).asString()).data());
			break;
		case ITEM_COLOR_BLUE:
			this->def += floor / 10 + 1;
			sGlobal->gameMap->showTip(("防御+" + Value(floor / 10 + 1).asString()).data());
			break;
	}
}

//获得剑
void Hero::getSword(const int type)
{
	int addAtk = 0;
	switch (type)
	{
		case WEAPON_TYPE_IRON:
			addAtk = 10;
			sword = "铁剑";
			break;
		case WEAPON_TYPE_SLIVER:
			addAtk = 20;
			sword = "银剑";
			break;
		case WEAPON_TYPE_KNIGHT:
			addAtk = 40;
			sword = "骑士剑";
			break;
		case WEAPON_TYPE_HOLY:
			addAtk = 50;
			sword = "神圣剑";
			break;
	}
	sGlobal->gameMap->showTip(("获得"+sword+"\n攻击+" + Value(addAtk).asString()).data());
	this->atk += addAtk;
}

//获得盾
void Hero::getShield(const int type)
{
	int addDef = 0;
	switch (type)
	{
		case WEAPON_TYPE_IRON:
			addDef = 10;
			sword = "铁盾";
			break;
		case WEAPON_TYPE_SLIVER:
			addDef = 20;
			sword = "银盾";
			break;
		case WEAPON_TYPE_KNIGHT:
			addDef = 40;
			sword = "骑士盾";
			break;
		case WEAPON_TYPE_HOLY:
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