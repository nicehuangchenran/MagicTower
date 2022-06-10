#ifndef __TELEPORT_H__
#define __TELEPORT_H__

#include "cocos2d.h"
#include "Headers.h"
USING_NS_CC;

class Teleport:public Ref
{
public:
	Teleport(const ValueMap& dict,const int x, const int y);
	~Teleport();

	Point telePosition; // ������λ�ã�Scene����GL���꣬��Ҫת��
	int targetID; // Ŀ���ͼ��������hero.cpp�б���ȡȻ���л�����
	Point targetHeroPosition;  // Ŀ���ͼӢ�۳�ʼλ�ã�Tile���꣩

};

#endif
