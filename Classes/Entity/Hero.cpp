#include "Hero.h"
#include "Constants.h"

Hero::Hero() {
	sGlobal->hero = this;
}

Hero::~Hero() {}


//创建对象
Hero* Hero::create()
{
	//new申请空间
	Hero* heroPointer = new(std::nothrow) Hero;

	//异常处理
	if (heroPointer && heroPointer->init())
	{
		return heroPointer;
	}
	else
	{
		delete heroPointer;
		return nullptr;
	}
}

//初始化对象
bool Hero::init()
{
	//调用父类初始化函数
	if (!Node::init())
	{
		return false;
	}

	//初始化状态数据
	position = Point(0, 0);
	atk = 10;
	def = 10;
	blood = 400;
	gold = 100;
	key[ITEM_COLOR_YELLOW] = 0;
	key[ITEM_COLOR_BLUE] = 0;
	key[ITEM_COLOR_RED] = 0;

	//设置精灵
	heroImage = Sprite::create("img/1.png", 
		Rect(0, OBJECT_SIZE*10+1, OBJECT_SIZE,OBJECT_SIZE));//创建精灵
	heroImage->setAnchorPoint(Point::ZERO);//设置锚点为左下角
	this->addChild(heroImage);//绑定精灵

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

	//碰撞检测

	//修改位置状态
	targetGLPosition += moveDist;

	//动画

	auto heroTexture = Director::getInstance()->getTextureCache() -> addImage("img/1.png");

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
	//auto animate = Animate::create(animation);
	heroImage->runAction(Repeat::create(Animate::create(animation), 1));
	this -> heroImage ->
		setTextureRect(Rect(0, OBJECT_SIZE * faceDirection + 1, OBJECT_SIZE, OBJECT_SIZE));
	this->runAction(MoveBy::create(0.2f, moveDist));
}

CollisionType Hero::collisionCheck(Vec2 heroPosition)
{
	targetTilePosition = sGlobal->gameMap->tileCoordForPosition(heroPosition);
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

	// 对应图块是门
	targetTileGID = sGlobal->gameMap->getDoorLayer()->getTileGIDAt(targetTilePosition);
	if (targetTileGID)
	{
		// opendoor() 开门
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

