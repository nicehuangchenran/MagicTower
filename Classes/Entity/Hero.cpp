#include "Headers.h"

Hero::Hero() {}

Hero::~Hero() 
{
	delete fightLayer;
}

//创建对象
Hero* Hero::create(Vec2 tilePosition)
{
	//new申请空间
	static Hero* heroPointer = new Hero;

	//异常处理
	if (heroPointer && heroPointer->init(tilePosition))
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
bool Hero::init(Vec2 tilePosition)
{
	//调用父类初始化函数
	if (!Node::init()) { return false; }

	//初始化状态数据
	targetTilePosition = tilePosition;
	targetGLPosition = tilePosition * OBJECT_SIZE;
	blood = INIT_BLOOD;
	atk = INIT_ATK;
	def = INIT_DEF;
	gold = INIT_GOLD;
	key[ITEM_COLOR_YELLOW] = 0;
	key[ITEM_COLOR_BLUE] = 0;
	key[ITEM_COLOR_RED] = 0;

	//战斗界面
	fightLayer = new FightLayer;

	//设置精灵
	image = Sprite::create("img/1.png", Rect(0, OBJECT_SIZE * 10 + 1, OBJECT_SIZE, OBJECT_SIZE));//创建精灵
	image->setAnchorPoint(Point::ZERO);//设置锚点为左下角
	
	this->addChild(image);//绑定精灵

	return true;
}

//移动一格
void Hero::move(EventKeyboard::KeyCode code)
{
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
	}

	//计算目标位置
	targetGLPosition = this->getPosition() + moveDist;
	targetGLPosition.x -= 160;  // 将GL坐标系原点设为(160,0)，待用函数封装
	//测试坐标
	//log("%d, %d", sGlobal->gameMap->getMapSize().width, sGlobal->gameMap->getMapSize().height);
	
	//碰撞检测
	
	CollisionType colli = collisionCheck(targetGLPosition);

	if (colli == kWall || colli == kEnemy || colli == kDoor || colli == kNPC)
	{
		// 脸部方向改变，绘制新图
		this->image->setTextureRect(Rect(0, OBJECT_SIZE * faceDirection + 1, OBJECT_SIZE, OBJECT_SIZE));
		return;
	}
	
	
	// 行走动画
	walkAnimation(faceDirection);

	// 脸部方向改变，绘制新图
	this->image->setTextureRect(Rect(0, OBJECT_SIZE * faceDirection + 1, OBJECT_SIZE, OBJECT_SIZE));

	// 移动到新位置
	this->runAction(MoveBy::create(0.2f, moveDist));
}


void Hero::walkAnimation(int faceDirection)
{
	auto heroTexture = Director::getInstance()->getTextureCache()->addImage("img/1.png");

	SpriteFrame* frame0 = SpriteFrame::createWithTexture(heroTexture,
		Rect(OBJECT_SIZE * 0, OBJECT_SIZE * faceDirection, OBJECT_SIZE, OBJECT_SIZE));
	SpriteFrame* frame1 = SpriteFrame::createWithTexture(heroTexture,
		Rect(OBJECT_SIZE * 1, OBJECT_SIZE * faceDirection, OBJECT_SIZE, OBJECT_SIZE));
	SpriteFrame* frame2 = SpriteFrame::createWithTexture(heroTexture,
		Rect(OBJECT_SIZE * 2, OBJECT_SIZE * faceDirection, OBJECT_SIZE, OBJECT_SIZE));
	SpriteFrame* frame3 = SpriteFrame::createWithTexture(heroTexture,
		Rect(OBJECT_SIZE * 3, OBJECT_SIZE * faceDirection, OBJECT_SIZE, OBJECT_SIZE));
	Vector<SpriteFrame*> animFrames;
	animFrames.pushBack(frame0);
	animFrames.pushBack(frame1);
	animFrames.pushBack(frame2);
	animFrames.pushBack(frame3);
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
	image->runAction(Repeat::create(Animate::create(animation), 1));

}

CollisionType Hero::collisionCheck(Vec2 targetGLPosition)
{
	targetTilePosition = sGlobal -> gameMap -> tileCoordForPosition(targetGLPosition);
	// 地图边界
	
	if (targetTilePosition.x < 0 || targetTilePosition.y < 0 ||
		targetTilePosition.x > sGlobal->gameMap->getMapSize().width - 1 ||
		targetTilePosition.y > sGlobal->gameMap->getMapSize().height - 1)
	{
		return kWall;
	}

	// 对应图块是地图内的墙
	targetTileGID = sGlobal->gameMap->getWallLayer()->getTileGIDAt(targetTilePosition);
	if (targetTileGID)	return kWall;
	// 对应图块是怪物
	
	targetTileGID = sGlobal->gameMap->getEnemyLayer()->getTileGIDAt(targetTilePosition);
	if (targetTileGID) 
	{ 
		// fight() 开始战斗
		return kEnemy; 
	}
	
	targetTileGID = sGlobal->gameMap->getItemLayer()->getTileGIDAt(targetTilePosition);
	if (targetTileGID)
	{
		getKey(ITEM_COLOR_YELLOW);  // 得到道具（判断颜色）
		sGlobal->gameMap->getItemLayer()->removeTileAt(targetTilePosition);  // 删除道具
		return kEnemy;
	}
	// 对应图块是门
	targetTileGID = sGlobal->gameMap->getDoorLayer()->getTileGIDAt(targetTilePosition);
	if (targetTileGID)
	{
		// 门检测，减钥匙
		// ...
		// 删除门
		sGlobal->gameMap->getDoorLayer()->removeTileAt(targetTilePosition);
		return kDoor;
	}


	return kNone;
}

//获得钥匙
void Hero::getKey(const int color)
{
	this->key[color]++;
}

//获得药水
//---待修改：血量增加需要乘上系数【当前区域数】---
void Hero::getPotion(const int color)
{
	int addBlood = 0;
	switch (color)
	{
		case ITEM_COLOR_RED:
			addBlood = 50;
			break;
		case ITEM_COLOR_BLUE:
			addBlood = 200;
			break;
	}
	this->blood += addBlood;
}

//获得宝石
//---待修改：攻防增加需要乘上系数【当前区域数】---
void Hero::getGem(const int color)
{
	switch (color)
	{
		case ITEM_COLOR_RED:
			this->atk += 1;
			break;
		case ITEM_COLOR_BLUE:
			this->def += 1;
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
			break;
		case WEAPON_TYPE_SLIVER:
			addAtk = 20;
			break;
		case WEAPON_TYPE_KNIGHT:
			addAtk = 40;
			break;
		case WEAPON_TYPE_HOLY:
			addAtk = 50;
			break;
	}
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
			break;
		case WEAPON_TYPE_SLIVER:
			addDef = 20;
			break;
		case WEAPON_TYPE_KNIGHT:
			addDef = 40;
			break;
		case WEAPON_TYPE_HOLY:
			addDef = 50;
			break;
	}
	this->def += addDef;
}

void Hero::fightWithEnemy(Scene* scene, const int enemyID)
{
	//禁用其他动作
	this->isStopping = 0;

	//检查怪物ID是否正确
	if (enemyID < 1 || enemyID > ENEMY_NUM) { return; }

	//获取怪物信息
	Enemy* enemy = new Enemy; //在fightLayer->fight(this, enemy)里delete
	*enemy = sGlobal->enemyMap[enemyID];

	//初始化显示
	scene->addChild(fightLayer);//fightLayer不能作为hero的child
	fightLayer->initDisplay(this, enemy);

	//进行回合制战斗
	fightLayer->fight(scene, this, enemy);
}