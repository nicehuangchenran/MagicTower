#ifndef _HERO_H_
#define _HERO_H_

#include "cocos2d.h"
#include "Constants.h"
#include "FightLayer.h"
#include "Scene/test_start.h"

USING_NS_CC;

class FightLayer;
class test_start;

class Hero :public Node {
public:
	enum Color {
		YELLOW = 0,
		BLUE,
		RED,
		ULTRA,
	};
	int faceDirection;
	Hero();
	~Hero();
	static Hero* create(test_start* scene, Vec2 position); //创建对象
	bool init(test_start* scene, Vec2 position); //初始化对象
	void move(EventKeyboard::KeyCode code); //移动一格

	void getItem(const int gid);
	void getKey(const int color); //获得钥匙
	void getPotion(const int color); //获得药水
	void getGem(const int color); //获得宝石
	void getSword(const int type); //获得剑
	void getShield(const int type); //获得盾
	void fightWithEnemy(const int enemyID, Vec2 targetTilePosition); //与怪物战斗
	void walkAnimation(const int faceDirection); // 行走动画
	void moveIsDone(Node* node, void* faceDirection); //将状态置为停止
	CollisionType collisionCheck(Vec2 targetGLPosition); // 判断碰撞类型
	
	int keyNum(const int color);
	int bldNum();
	int atkNum();
	int defNum();
	int mnyNum();
	std::string swordName();
	std::string shieldName();

	void openDoor(const int gid, const int color); //开门动作
	void updateOpenDoorAnimation(float time); //更新开门动画

	int targetDoorGID;
	bool isStopping; //是否处于静止状态（用于动画时禁止其他操作）
	
	test_start* scene; //当前所在场景
	int floor; //当前所在层数
	FightLayer* fightLayer; //战斗界面

	friend class FightLayer; //允许战斗时改变自己的属性
	
protected:
	Sprite* image; //勇士形象图片
	Vec2 targetTilePosition;  // 目标位置的Tile坐标
	Vec2 targetGLPosition;  // 目标位置的openGL坐标
	int targetTileGID; // 目标位置的GID数据

	int atk; //攻击力
	int def; //防御力
	int blood; //血量
	int gold; //金币
	int key[4]; //拥有钥匙数
	std::string sword;
	std::string shield;
};
#endif