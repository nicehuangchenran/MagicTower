#include "Headers.h"

void Global::initEnemyMap()
{
	std::ifstream in;
	in.open("..\\Resources\\EnemyInfo.txt", std::ios::in);
	if (!in.is_open()) { return; }
	for (int i = 1; i <= ENEMY_NUM; ++i)
	{
		Enemy& info = this->enemyMap[i];
		in >> info.name
			>> info.blood
			>> info.atk
			>> info.def
			>> info.gold
			>> info.type
			>> info.graphPosition.x
			>> info.graphPosition.y;
	}
	in.close();
}