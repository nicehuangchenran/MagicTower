#ifndef _HERO_H_
#define _HERO_H_

#include "cocos2d.h"

USING_NS_CC;

class Hero :public Node {
public:
	Hero();
	~Hero();
	static Hero* create(); //��������
	bool init(); //��ʼ������
	void move(const int direction); //�ƶ�һ��
	//CollisionType collisionCheck(Vec2 heroPosition);
	void getKey(const int color); //���Կ��
	void getPotion(const int color); //���ҩˮ
	void getGem(const int color); //��ñ�ʯ
	void getSword(const int type); //��ý�
	void getShield(const int type); //��ö�
	
protected:
	Sprite* sprite; //����
	Point position; //λ��
	int atk; //������
	int def; //������
	int blood; //Ѫ��
	int gold; //���
	int key[3]; //ӵ��Կ����
};

#endif // !_HERO_H_