#include "Hero.h"

Hero::Hero() {

}

Hero::~Hero() {

}

Hero* Hero::create() {
	//new����ռ�
	Hero* heroPointer = new(std::nothrow) Hero;

	//�쳣����
	if (heroPointer && heroPointer->init()) {
		return heroPointer;
	}
	else {
		delete heroPointer;
		return nullptr;
	}
}

bool Hero::init() {
	//���ø����ʼ������
	if (!Node::init()) {
		return false;
	}

	//���г�ʼ��

	return true;
}