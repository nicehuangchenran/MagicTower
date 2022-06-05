#include "Hero.h"

Hero::Hero() {

}

Hero::~Hero() {

}

Hero* Hero::create() {
	//new申请空间
	Hero* heroPointer = new(std::nothrow) Hero;

	//异常处理
	if (heroPointer && heroPointer->init()) {
		return heroPointer;
	}
	else {
		delete heroPointer;
		return nullptr;
	}
}

bool Hero::init() {
	//调用父类初始化函数
	if (!Node::init()) {
		return false;
	}

	//进行初始化

	return true;
}