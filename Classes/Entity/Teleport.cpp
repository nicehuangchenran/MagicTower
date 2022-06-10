#include "Teleport.h"


Teleport::Teleport(const ValueMap& dict, const int x, const int y)
{
	int rectX = dict.at("RecX").asInt();
	int rectY = dict.at("RecY").asInt();

	telePosition = Point(x+160, y);  // �����ŵ�λ�ã�����160����Ϊtest_start��Scene����������Layer
	
	targetID = dict.at("targetMap").asInt();  // Ŀ���ͼ�Ĳ���
	//log("%d", targetID);
	targetHeroPosition = sGlobal -> gameMap -> positionForTileCoord(Point(dict.at("heroTileCoordX").asInt(),  // Ŀ���ͼӢ�۵���ʼ����
	dict.at("heroTileCoordY").asInt()));
	targetHeroPosition.x += 160;

	auto teleport = Sprite::create("img/1.png", 
		Rect(rectX * OBJECT_SIZE, rectY*OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE) );  // ���������ž���
	teleport->setAnchorPoint(Vec2::ZERO);
	teleport->setPosition(Vec2(telePosition));

	sGlobal->test_start->addChild(teleport,1);

}

Teleport::~Teleport()
{

}