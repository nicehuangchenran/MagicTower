## Git


    问题 : fatal: Could not read from remote repository
    
    解决 : 将.git/commit中的url改为https格式
    
    例子 : url = https://github.com/nicehuangchenran/MagicTower.git

## Cocos

1. 焦骜：cocos2d audio里SimpleAudioEngine没有实现音量大小控制代码（永远返回1.0）需要自己加上相应代码。解决：使用AudioEngine来替代SimpleAudioEngine
1. 

## 其他

##### 注意事项：

1、头文件前统一格式，形如：#ifndef \_WORD1_WORD2_H_

2、包含头文件时若在不同文件夹记得加上路径

3、windows平台上每次pull重新cmake后需要 右键项目-属性-配置属性-C/C++-命令行 输入/utf-8

4、代码风格和命名格式最后需要统一修改

5、需要包含系统头文件的内容不要写在.h文件中，会造成头文件重复包含和重定义，应写在.cpp文件中。

6、Headers.h供.cpp文件使用，.h文件尽量不要使用

7、创建新文件时记得修改高级保存选项



##### zzh：关于存档问题与类的设计：

我思考了一下游戏中类设计的问题，我把魔塔地图上的不同物体分为两种，一种是不可变的，比如上一关/下一关的台阶、普通的墙壁，这些可以作为一个类，每次进入一关就会先绘制出来；另一种是可变的，包括怪物、道具（能加属性的普通道具、钥匙、特殊道具三类）、NPC（商人、老人）、碰到之后会消失的墙壁等等，可以在Sprite类的基础上再套一个ChangableObject类来作为基类。这些物体的共同特点是主角坐标与其重合时会触发事件，那么我们可以用一个虚函数来描述触发的事件，这样的码量也不会多很多。在存档时，Cocos支持存档的类CCUserDefault可以存int、float、bool、string等等，我们可以在做关卡类的时候给每一关列一个ChangableObject的清单（考虑用map实现），每次触发事件的时候就可以判断一下是否把这个对象对应的bool值从1修改为0（1代表它还在地图上，0代表已经消失），然后存档的时候记录这些值，这样就很方便再读档。



##### lxy：继承体系预期设计：

```
Ref
{
	Node
	{
		ChangableObject
		{
			NPC
			Key：使用参数区分颜色
			Potion：使用参数区分颜色
			Gem：使用参数区分颜色
			Sword：使用参数区分种类
			Shield：使用参数区分种类
			Enemy
		}
	}
}
```

