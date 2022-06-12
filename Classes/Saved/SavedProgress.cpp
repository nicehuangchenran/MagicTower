#include "savedProgress.h"

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

SavedProgress::SavedProgress(void) {
	sGlobal->saved = this;
	//levels = new Map<int, GameMap>;
	//static GameMap* map0 = new GameMap;
	//levels->insert(0, *map0);
}

void SavedProgress::saveGame() {
	const int& levelNum = sGlobal->currentLevel;
	for (int i = 1; i <= levelNum; i++) {
		//此处saveEnemies的参数应为对应关卡
		//saveEnemies();
		//saveObject();
	}
}

void SavedProgress::saveLevel(const test_start* scene) {
	//此处需补全由levelNum到对应GameMap的转换
	//savedLevel* level = new savedLevel;
	//level->records[0] = saveObjects(map, "enemy");
	//*level.records[1] = saveObjects(map, "npc");
	//*level.records[2] = saveObjects(map, "door");
	//*level.records[3] = saveObjects(map, "item");

	sGlobal->levels[sGlobal->currentLevel - 1] = scene->_tileMap;
}

map<Point, int>* SavedProgress::saveObjects(const GameMap* map, const string& type) {
	std::map<Point, int>* info = new std::map<Point, int>;
	//TMXObjectGroup* group = map->objectGroupNamed("enemy");
	Vector<Enemy*> group = map->enemyArray;
	/*const ValueVector& objects = group->getObjects();

	for (ValueVector::const_iterator it = objects.begin(); it != objects.end(); it++) {
		//读取地图上存在的物品信息放入info
		const ValueMap& dict = (*it).asValueMap();
		Point* tile = new Point;
		tile->x = dict.at("x").asInt();
		tile->y = dict.at("y").asInt();
		
		info.insert({ GID, *tile });
	}*/
	for (Vector<Enemy*>::iterator it = group.begin(); it != group.end(); ++it) {
		//读取地图上存在的物品信息放入info
		Point tile = (*it)->graphPosition;
		int GID = (*it)->startGID;
		info->insert({ tile, GID });
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