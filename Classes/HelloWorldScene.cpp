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
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();  // 定义地图的可视化尺寸
    Vec2 origin = Director::getInstance()->getVisibleOrigin();  // 定义地图的可视化原点
    auto backgroudImage = Sprite::create("魔塔.png", Rect(240,0,550,483));
    backgroudImage -> setAnchorPoint(Vec2::ZERO);
    this -> addChild(backgroudImage);
    

    auto label = Label::createWithTTF("魔塔50层", "fonts/Songti.ttc", 40);
    auto magic_tower = Label::createWithTTF("Magic Tower", "fonts/Apple Chancery.ttf", 30);
    if (label == nullptr)
    {
        problemLoading("fonts/Songti.ttc");
    }
    if (magic_tower == nullptr)
    {
        problemLoading("fonts/Apple Chancery.ttf");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height * 3));
        magic_tower -> setPosition(Vec2(origin.x + visibleSize.width/2,
                                        origin.y + visibleSize.height - label->getContentSize().height * 4));
        // add the label as a child to this layer
        this -> addChild(magic_tower, 1);
        this->addChild(label, 1);
    }
    
    MenuItemFont::setFontName("fonts/arial.ttf");
    MenuItemFont::setFontSize(28);
    auto item1 = MenuItemFont::create("重新开始游戏");  // 文本菜单，接受两个参数，要显示的文本和回调函数指针
    auto item2 = MenuItemFont::create("载入存档");
    auto item3 = MenuItemFont::create("游戏说明");
    auto item4 = MenuItemFont::create("选项");
    auto item5 = MenuItemFont::create("退出游戏");

    
    // create menu, it's an autorelease object
    auto menu = Menu::create(item1, item2, item3, item4, item5, NULL);
    menu -> alignItemsVertically();
    menu->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height - label->getContentSize().height * 7));
    this->addChild(menu, 1);
     
    return true;
}



