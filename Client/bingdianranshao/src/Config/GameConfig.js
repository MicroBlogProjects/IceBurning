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
GC.IS_HOST = true;

var LAYER_PRIORITY_BACKGROUND = 0;			               //背景层优先级
var LAYER_PRIORITY_MAP = 5;                                //地图优先级
var LAYER_PRIORITY_TOUCH = 100;                                //点击层优先级
var LAYER_PRIORITY_MONSTER = 10;                                //怪物层优先级

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

var TMXTileMapsize = 32;

var HostUpPath = {"origin" : cc.p(5,12),
               "destination" : cc.p(7,16)};

var HostUpStraightPath = {"origin" : cc.p(5,16),
                             "destination" : cc.p(30,18)};

var HostStraightPath = {"origin" : cc.p(8,9),
                         "destination" : cc.p(30,11)};

var HostDownStraightPath = {"origin" : cc.p(5,2),
                           "destination" : cc.p(30,4)};

var HostDownPath = {"origin" : cc.p(5,4),
                  "destination" : cc.p(7,8)};

var AwayUpPath = {"origin" : cc.p(53,12),
                    "destination" : cc.p(55,16)};

var AwayUpStraightPath = {"origin" : cc.p(30,16),
                             "destination" : cc.p(55,18)};

var AwayStraightPath = {"origin" : cc.p(30,9),
                           "destination" : cc.p(52,11)};

var AwayDownStraightPath = {"origin" : cc.p(30,2),
                               "destination" : cc.p(55,4)};

var AwayDownPath = {"origin" : cc.p(53,4),
                      "destination" : cc.p(55,8)};

var HostPathConfig = {
    "UpPath" :[HostUpPath,],
    "StraightPath" : [HostUpStraightPath,HostStraightPath,HostDownStraightPath],
    "DownPath" :[HostDownPath,]
};



var  AwayPathConfig = {
    "UpPath" : [AwayUpPath,],
    "StraightPath" : [AwayUpStraightPath,AwayStraightPath,AwayDownStraightPath],
    "DownPath" : [AwayDownPath,]
};

var FightingPathConfig = {
    "UpPath" :[HostUpPath, AwayDownPath],
    "StraightPath" : [HostUpStraightPath,HostStraightPath,HostDownStraightPath,AwayUpStraightPath,AwayStraightPath,AwayDownStraightPath],
    "DownPath" :[HostDownPath,AwayUpPath]
}

//建筑物可以放得位置
var BuilddingPosition = {

};