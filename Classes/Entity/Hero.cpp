#include "Headers.h"

Hero::Hero() {}

Hero::~Hero() 
{
	delete fightLayer;
}

//创建对象
Hero* Hero::create()
{
	//new申请空间
	Hero* heroPointer = new Hero;

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
	if (!Node::init()) { return false; }

	//初始化状态数据
	position = Point(0, 0);
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
	sprite = Sprite::create("img/1.png", Rect(0, OBJECT_SIZE * 10 + 1, OBJECT_SIZE, OBJECT_SIZE));//创建精灵
	sprite->setAnchorPoint(Point::ZERO);//设置锚点为左下角
	this->addChild(sprite);//绑定精灵

	return true;
}

//移动一格
void Hero::move(const int direction)
{
	//确定移动的距离
	Point moveDist;
	switch (direction)
	{
		case DIRECTION_UP:
			moveDist = Point(0, OBJECT_SIZE);
			break;
		case DIRECTION_DOWN:
			moveDist = Point(0, -OBJECT_SIZE);
			break;
		case DIRECTION_LEFT:
			moveDist = Point(-OBJECT_SIZE, 0);
			break;
		case DIRECTION_RIGHT:
			moveDist = Point(OBJECT_SIZE, 0);
			break;
	}

	//碰撞检测

	//修改位置状态
	this->position += moveDist;

	//动画
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