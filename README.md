# 魔塔项目
>同济大学软件学院2022年高级程序设计（荣）课程项目
## 小组成员：黄晨冉 焦骜 张梓瀚 林鑫宇

## 评分项完成度
- 基本功能
  - [x] 开始界面
  - [x] 背景音乐
  - [x] 退出功能
  - [ ] 音量控制
  - [x] 暂停及恢复功能
  - [x] 至少十层
  - [x] 怪物种类三种，普通攻击、真实伤害、暴击，每类2-3种具体怪物
  - [x] 角色属性系统（生命、攻击、防御、金币）
  - [x] 道具系统（钥匙、药水、武器等）
  - [x] 标准回合制战斗
  - [x] 键盘控制角色移动
- 基础功能以外新功能
  - [x] 商店系统
  - [x] 无敌模式
  - [x] NPC对话和交互
  - [x] 游戏战斗、开门音效

## 亮点与加分项
1、贯彻且合理地使⽤了许多C++特性

2、程序基本不会崩溃

3、项⽬⽬录结构清晰

4、界⾯精致，还原魔塔

5、利用Const.h管理全局常量

6、程序很少崩溃

7、项目目录结构清晰

## C++新特性
* lambda表达式
  ```
  Action* action = Sequence::create(
		MoveBy::create(0.5f, Point(0, 48)),
		FadeOut::create(0.3f),
		[=]()
		{
			this->removeChild(label);
		},
		nullptr);
   ```
* 基于范围的for循环
  ```
     auto group = this->objectGroupNamed("object");
    const ValueVector& objects = group->getObjects();
    for (auto obj : objects)
    {
        const ValueMap& dict = obj.asValueMap();
        int x = dict.at("x").asInt();
        int y = dict.at("y").asInt();
  ```
* auto类型推断
  ```
  auto enemy = new Enemy;
  ```
* 初始化列表
  ```
  Global::Global() :
    gameScene(nullptr), gameMap(nullptr), hero(nullptr), saved(nullptr), paused(0),
    currentLevel(1), curMaxLevel(0), heroSpawnTileCoord(Point{ OBJECT_SIZE*10, OBJECT_SIZE })
  {
    initEnemyMap();
  };
  ```
## 魔塔游戏玩法

## 游戏简介
身为勇士的你必须闯过一层又一层的魔塔，魔塔里到处都充满着凶残的怪物，当然也有武器和补给，最后到达塔顶打败邪恶的大魔王——石头人，当角色血量为0或者打败大魔王游戏结束，返回主界面。

## 游戏控制
  -  键盘上下左右控制移动
  -  P暂停
  -  B返回主页面
  -  遇到怪物自动战斗，无法退出
