#include "Headers.h"

GameMap::GameMap()
{
    if (sGlobal->gameMap) //�ͷſռ�
    {
        delete sGlobal->gameMap;
    }
	sGlobal->gameMap = this;
}

GameMap* GameMap::create(const char* filePath)
{
    GameMap* gameMapP = new GameMap();
    if (gameMapP->initWithTMXFile(filePath))
    {
        gameMapP->mapInit();
        return gameMapP;
    }
    else
    {
        delete gameMapP;
        return nullptr;
    }
}

void GameMap::mapInit()
{
   
   
    floorLayer = this->getLayer("floor");
    wallLayer = this->getLayer("wall");
    itemLayer = this->getLayer("item");
    doorLayer = this->getLayer("door");

    initEnemy();
    //initObject();
}

void GameMap::initEnemy()
{
	enemyLayer = this->getLayer("enemy");

	Size s = enemyLayer->getLayerSize();

	
	for (int x = 0; x < s.width; x++)
	{
		for (int y = 0; y < s.height; y++)
		{
			int gid = enemyLayer->getTileGIDAt(Point(x, y));
			if (gid != 0)
			{
				Enemy* enemy = new Enemy();

				
				enemy->graphPosition = Point(x, y);

				
				enemy->startGID = gid;

				//��һ����bug�����Ҹ���
				//enemyArray.pushBack(enemy);
			}
		}
	}

	
}

Point GameMap::tileCoordForPosition(Point position)
{
    int x = position.x / this->getTileSize().width;
    int y = (((this->getMapSize().height - 1) * this->getTileSize().height) - position.y) / this->getTileSize().height;
    return Point(x, y);
}

void GameMap::showTip(const char* tip, Point startPosition) {
    //�½�һ���ı���ǩ
    LabelTTF* tipLabel = LabelTTF::create(tip, "Arial", 20);

    tipLabel->setPosition(startPosition + Point(16, 16));

    this->addChild(tipLabel, kZTip, kZTip);

    //���嶯��Ч��
    Action* action = Sequence::create(
        MoveBy::create(0.5f, Point(0, 32)),
        DelayTime::create(0.5f), FadeOut::create(0.2f),
        CallFuncN::create(CC_CALLBACK_1(GameMap::onShowTipDone, this)),
        NULL);

    tipLabel->runAction(action);
}

void GameMap::onShowTipDone(Node* pSender) {
    //ɾ���ı���ǩ
    this->getChildByTag(kZTip)->removeFromParentAndCleanup(true);
}

void GameMap::showInfo(const char* info, int time) {
    auto label = Label::createWithTTF(info, "fonts/Marker Felt.ttf", 36);
    label->setPosition(100, 200); //���ñ�ǩλ��
    label->enableShadow(Color4B::GREEN, Size(10, 10)); //������ӰЧ��
    label->enableOutline(Color4B::RED, 3); //���ñ߿�Ч��
    this->addChild(label, 0); //���뵽������
    Sleep(time);
    this->removeChild(label);
}