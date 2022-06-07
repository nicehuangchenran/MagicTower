#include "Enemy.h"
#include <map>

// 怪物名到怪物ID的映射
std::map<std::string, int> enemyID; //其他地方要用时使用extern

Enemy::Enemy() {
	dictIdx = 0;
	graphID = 0;
}

Enemy::~Enemy() {

}

void Enemy::meetWithHero() {

}