#include "Headers.h"

/*
SavedProgress::SavedProgress(void) {
	if (map == nullptr)
		map = sGlobal->gameMap;
	setIntegerForKey("level", sGlobal->currentLevel);
}

void SavedProgress::saveLevel(const int& levelNum) {

}

void SavedProgress::saveEnemies() {
	TMXObjectGroup* group = map->objectGroupNamed("enemy");
	const ValueVector& enemies = group->getObjects();
	
	for (ValueVector::const_iterator it = enemies.begin(); it != enemies.end(); it++) {
		const ValueMap& dict = (*it).asValueMap();
		const char* key = dict.at("ID").asString().c_str();
		setStringForKey(key, stringFromDict(dict));
		flush();
	}
}

string SavedProgress::stringFromDict(const ValueMap& dict) {
	string s;
	s += dict.at("x").asString();
	s += "_";
	s += dict.at("y").asString();
	s += "_";
	return s;
}*/

SavedProgress::SavedProgress(void) 
{
	sGlobal->saved = this;
	//levels = new Map<int, GameMap>;
	//static GameMap* map0 = new GameMap;
	//levels->insert(0, *map0);
}

void SavedProgress::saveGame() 
{
	const int& levelNum = sGlobal->currentLevel;
	for (int i = 1; i <= levelNum; i++) 
	{
		//此处saveEnemies的参数应为对应关卡
		//saveEnemies();
		//saveObject();
	}
}

void SavedProgress::saveLevel(const GameScene* scene)
{
	sGlobal->savedLevels[sGlobal->currentLevel - 1] = scene->_tileMap;
}

map<Point, int>* SavedProgress::saveObjects(const GameMap* map, const string& type) 
{
	auto info = new std::map<Point, int>;
	//TMXObjectGroup* group = map->objectGroupNamed("enemy");
	/*const ValueVector& objects = group->getObjects();

	for (ValueVector::const_iterator it = objects.begin(); it != objects.end(); it++) {
		//读取地图上存在的物品信息放入info
		const ValueMap& dict = (*it).asValueMap();
		Point* tile = new Point;
		tile->x = dict.at("x").asInt();
		tile->y = dict.at("y").asInt();
		
		info.insert({ GID, *tile });
	}*/
	auto enemyLayer = sGlobal->gameMap->getLayer("enemy");
	Size s = enemyLayer->getLayerSize();
	for (int x = 0; x < s.width; x++)
	{
		for (int y = 0; y < s.height; y++)
		{
			int gid = enemyLayer->getTileGIDAt(Point(x, y));
			if (gid)
			{
				info->insert({ Point(x,y), gid });
			}
		}
	}
	return info;
}
/*
map<Point, int>* SavedProgress::getObjects(const int& levelNum, const string& type) {
	int layerNum;
	if (type == "enemy") layerNum = 0;
	else if (type == "npc") layerNum = 1;
	else if (type == "door") layerNum = 2;
	else if (type == "item") layerNum = 3;
	return levels->at(levelNum)->records[layerNum];
}*/