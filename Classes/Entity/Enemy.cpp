#include "Enemy.h"

Enemy::Enemy() {}

Enemy::~Enemy() {}

Enemy& Enemy::operator =(const Enemy& e)
{
	this->blood = e.blood;
	this->atk = e.atk;
	this->def = e.def;
	this->gold = e.gold;
	this->type = e.type;
	this->graphPosition = e.graphPosition;
	return *this;
}
