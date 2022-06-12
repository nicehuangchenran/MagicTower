#include "Introduction.h"
#include "SettingScene.h"
#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC; 
using namespace CocosDenshion;

Scene* Introduction::createScene()
{
    return Introduction::create();
}

bool Introduction::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //添加说明文本
    auto richText = cocos2d::ui::RichText::create();
    richText -> ignoreContentAdaptWithSize(false);
    richText->setContentSize(Size(600, 400));
    cocos2d::ui::RichElementText* introText = cocos2d::ui::RichElementText::create(0, Color3B::WHITE, 255, "这是一个很古老的故事：\n很久很久以前，在遥远的西方大地上，有着这样一个王国，王国虽小但全国人们都过着幸福快乐的生活。\n突然有一天，从天空飞来一群可怕的怪物，他们来到皇宫，抢走了国王唯一的女儿。\n第二天，国王便向全国下达了紧急令，谁能将公主找回来，便将王位让给他。\n于是，全国的勇士们都出发了，他们的足迹走遍了全国的各个角落。\n而我们的故事，就从这里开始. . .", "fonts/Songti.ttc", 20);
    richText -> pushBackElement(introText);
    richText->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 20));
    addChild(richText);
    
    //添加返回控件
    auto ok = MenuItemFont::create("完成", CC_CALLBACK_1(Introduction::menuItemBack, this));
    ok -> setPosition(Vec2(origin.x + visibleSize.width/2, 50));
    auto menu = Menu::create(ok,nullptr);
    menu -> setPosition(Vec2::ZERO);
    addChild(menu);
    
    return true;
}

void Introduction::menuItemBack(Ref *PSender)
{
    if (Setting::isEffect)  SimpleAudioEngine::getInstance()->playEffect("button_click.wav");
    Director::getInstance() -> popScene();
}
