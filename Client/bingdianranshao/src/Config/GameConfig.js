/**
 * Created by jiachen on 2016/3/28.
 */

var GC = GC || {};
GC.winSize = cc.size(960, 640);
GC.h = GC.winSize.height;
GC.w = GC.winSize.width;
GC.w_2 = GC.winSize.width / 2 ;
GC.h_2 = GC.winSize.height / 2;
GC.SOUND_ON = true;
GC.UIN = -1;
GC.NUM_MONSTER_BLOCK = 2;

GC.IS_HOST = false; //true 表示主场也是左边这个阵营， false表示客场也是右边这个阵营

GC.ISWIN = false;
GC.CoidNum = 100;
GC.hasCreateRoom = 0;
GC.Frame = 0;

var LAYER_PRIORITY_BACKGROUND = 0;			               //背景层优先级
var LAYER_PRIORITY_MAP = 5;                                //地图优先级
var LAYER_PRIORITY_MONSTER = 10;                                //怪物层优先级
var LAYER_PRIORITY_TOUCH = 100;                                //点击层优先级
//向左走为-1 向右走位1 死亡 0 向左攻击为 -2 向右攻击为 2

var UserOperatorType = {
    "Monster" : 1,
    "Settlement" : 2
};

//当前怪物的动画状态
var MonsterState ={
    WalkingLeft :0,
    WalkingRight : 1,
    AttackLeft : 2,
    AttackRight : 3,
    Death : 4
};

var MonsterType ={
    Building: 0,
    Animal: 1
};

var MAXMonsterAccount = 5;
var MAXBuildingAccount = 3;
var MonsterIDList = [];
var BuildingIDlist = [];

var stepList = [];

//远程攻击动画种类
var MonsterAnimateKind = {
    "StraightAnimate" : 1,
    "ArcAnimate" : 2,
    "pointAnimate" : 3
};