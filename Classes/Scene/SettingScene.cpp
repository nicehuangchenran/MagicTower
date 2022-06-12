//
//  SettingScene.cpp
//  MagicTower
//
//  Created by 焦骜 on 2022/6/1.
//

#include "SettingScene.h"
#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC; 
using namespace CocosDenshion;

bool Setting::isEffect = true;

//当文件不存在时打印错误信息
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Scene* Setting::createScene()
{
    return Setting::create();
}

bool Setting::init()
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

    //音量开关
    auto toggleSoundMenuitem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuItemSoundToggleCallback, this), MenuItemFont::create(isEffect ? "on" : "off"), MenuItemFont::create(isEffect ? "off" : "on"), nullptr);
    toggleSoundMenuitem->setPosition(Vec2(450, 300));

    //添加选项说明
    auto soundLabel = MenuItemFont::create("音效：");
    soundLabel->setPosition(Vec2(250, 300));
    addChild(soundLabel);
    auto musicLabel = MenuItemFont::create("音乐：");
    musicLabel->setPosition(Vec2(250, 200));
    addChild(musicLabel);

    //添加滑动条
    cocos2d::ui::Slider* slider = cocos2d::ui::Slider::create();
    slider->loadBarTexture("Slider_Back.png"); // what the slider looks like
    slider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
    slider->loadProgressBarTexture("Slider_PressBar.png");
    slider->setMaxPercent(100);
    slider->setPercent(50);
    slider->setPosition(Vec2(450, 200));
    slider->addEventListener(CC_CALLBACK_2(Setting::onChangedSlider, this));
    addChild(slider);

    //完成按钮
    auto okMenuItem = MenuItemFont::create("完成", CC_CALLBACK_1(Setting::menuItemBack, this));
    okMenuItem->setPosition(Vec2(visibleSize.width / 2, 50));

    //将开关和完成加入菜单
    auto menu = Menu::create(toggleSoundMenuitem, okMenuItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    addChild(menu);
    return true;
}

void Setting::onChangedSlider(Ref* PSender, cocos2d::ui::Slider::EventType type)
{
    if (type == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        auto slider = dynamic_cast<cocos2d::ui::Slider*>(PSender);
        float percent = slider->getPercent() / 100.0f;
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(percent);
    }
}

void Setting::menuItemSoundToggleCallback(cocos2d::Ref* PSender)
{
    auto soundToggleMenuItem = (MenuItemToggle*) PSender;
    if (isEffect)
    {
        SimpleAudioEngine::getInstance() -> playEffect("button_click.wav");
    }
    isEffect ^= 1;
}

void Setting::menuItemBack(cocos2d::Ref* Psender)
{
    if (isEffect)
    {
        SimpleAudioEngine::getInstance()->playEffect("button_click.wav");
    }
    Director::getInstance()->popScene();
}

