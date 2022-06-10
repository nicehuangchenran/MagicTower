#ifndef _HERO_H_
#define _HERO_H_

#include "cocos2d.h"
USING_NS_CC;

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
	static Hero* create(Vec2 position); //创建对象
	bool init(Vec2 position); //初始化对象
	void move(EventKeyboard::KeyCode code); //移动一格

	void getItem(int gid);
	void getKey(const int color); //获得钥匙
	void getPotion(const int color); //获得药水
	void getGem(const int color); //获得宝石
	void getSword(const int type); //获得剑
	void getShield(const int type); //获得盾

	void fightWithEnemy(Scene* scene, const int enemyID); //与怪物战斗
	void walkAnimation(int faceDirection);  // 行走动画
	CollisionType collisionCheck(Vec2 targetGLPosition);  // 判断碰撞类型
	
	int keyNum(int col);
	int bldNum();
	int atkNum();
	int defNum();
	int mnyNum();

	void openDoor(int gid);
	void updateOpenDoorAnimation(float time); //开门动画
	int targetDoorGID;
	
	bool isStopping; //是否处于静止状态（用于动画时禁止其他操作）
	bool isDoorOpening;

	friend class FightLayer;
	
protected:
	Sprite* image; //勇士形象图片
	Vec2 targetTilePosition;  // 目标位置的Tile坐标
	Vec2 targetGLPosition;  // 目标位置的openGL坐标
	int targetTileGID; // 目标位置的GID数据


	FightLayer* fightLayer; //战斗界面

	int atk; //攻击力
	int def; //防御力
	int blood; //血量
	int gold; //金币
	int key[5]; //拥有钥匙数
};

#endif // !_HERO_H_