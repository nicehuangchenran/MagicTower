/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SettingScene.h"
#include "GameScene.h"
#include "Introduction.h"
#include "SimpleAudioEngine.h"

USING_NS_CC; 
using namespace CocosDenshion;

//当文件不存在时打印错误信息
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}


bool HelloWorld::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //添加背景图片
    auto backgroundImage = Sprite::create("mota.jpg");
    if (backgroundImage == nullptr)
    {
        problemLoading("mota.jpg");
    }
    else
    {
        backgroundImage->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        backgroundImage->setPosition(visibleSize / 2);
        this->addChild(backgroundImage);
    }

    //添加游戏标题
    auto chineseTitle = Label::createWithTTF("魔塔", "fonts/Songti.ttc", 50);
    auto englishTitle = Label::createWithTTF("Magic Tower", "fonts/Apple Chancery.ttf", 30);
    if (chineseTitle == nullptr)
    {
        problemLoading("fonts/Songti.ttc");
    }
    if (englishTitle == nullptr)
    {
        problemLoading("fonts/Apple Chancery.ttf");
    }
    else
    {
        chineseTitle->setPosition(Vec2(origin.x + visibleSize.width / 2, 300));
        englishTitle->setPosition(Vec2(origin.x + visibleSize.width / 2, 250));
        this->addChild(chineseTitle);
        this->addChild(englishTitle);
    }

    //添加菜单控件
    MenuItemFont::setFontName("fonts/arial.ttf");
    MenuItemFont::setFontSize(28);
    auto item1 = MenuItemFont::create("开始新游戏", CC_CALLBACK_1(HelloWorld::menuItemStart, this));
    auto item2 = MenuItemFont::create("载入存档");
    auto item3 = MenuItemFont::create("游戏说明", CC_CALLBACK_1(HelloWorld::menuItemIntro, this));
    auto item4 = MenuItemFont::create("选项设置", CC_CALLBACK_1(HelloWorld::menuItemSetting, this));
    auto item5 = MenuItemFont::create("退出游戏", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    //添加菜单
    auto menu = Menu::create(item1, item2, item3, item4, item5, nullptr);
    menu->alignItemsVertically();
    menu->setPosition(Point(origin.x + visibleSize.width / 2, 110));
    this->addChild(menu);

    //添加背景音乐
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic("backgroundMusic.wav", true);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);
    
    return true;
}

void HelloWorld::menuItemSetting(cocos2d::Ref* PSender)
{
    if (Setting::isEffect)    SimpleAudioEngine::getInstance()->playEffect("button_click.wav");
    Director::getInstance()->pushScene(TransitionFadeTR::create(1.0f, Setting::createScene()));
}

void HelloWorld::menuCloseCallback(cocos2d::Ref* PSender)
{
    if (Setting::isEffect) SimpleAudioEngine::getInstance()->playEffect("button_click.wav");
    Director::getInstance()->end();
}

void HelloWorld::menuItemIntro(Ref *PSender)
{
    if (Setting::isEffect) SimpleAudioEngine::getInstance()->playEffect("button_click.wav");
    Director::getInstance()->pushScene(TransitionFadeTR::create(1.0f, Introduction::createScene()));
}

void HelloWorld::menuItemStart(Ref* PSender)
{
    if (Setting::isEffect)  SimpleAudioEngine::getInstance()->playEffect("button_click.wav");
    Director::getInstance()->pushScene(TransitionFadeTR::create(1.0f, GameScene::createScene()));
}