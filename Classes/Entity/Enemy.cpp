#include "Enemy.h"
#include <map>

// ������������ID��ӳ��
std::map<std::string, int> enemyID; //�����ط�Ҫ��ʱʹ��extern

Enemy::Enemy() {
	dictIdx = 0;
	graphID = 0;
}

Enemy::~Enemy() {

}

void Enemy::meetWithHero() {

}