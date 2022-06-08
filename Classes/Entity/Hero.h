#ifndef _HERO_H_
#define _HERO_H_

#include "cocos2d.h"

USING_NS_CC;

class Hero :public Node {
public:
	Hero();
	~Hero();
	static Hero* create(); //创建对象
	bool init(); //初始化对象
	void move(const int direction); //移动一格
	//CollisionType collisionCheck(Vec2 heroPosition);
	void getKey(const int color); //获得钥匙
	void getPotion(const int color); //获得药水
	void getGem(const int color); //获得宝石
	void getSword(const int type); //获得剑
	void getShield(const int type); //获得盾
	
protected:
	Sprite* sprite; //精灵
	Point position; //位置
	int atk; //攻击力
	int def; //防御力
	int blood; //血量
	int gold; //金币
	int key[3]; //拥有钥匙数
};

#endif // !_HERO_H_