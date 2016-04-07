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
GC.IS_HOST = false;

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

var HostPathConfig = {
    "UpPath" :[{"origin" : cc.p(5,12), "destination" : cc.p(7,16)},
                {"origin" : cc.p(5,16),"destination" : cc.p(30,18)}],
    "MiddlePath" : [{"origin" : cc.p(8,9),"destination" : cc.p(30,11)}],
    "DownPath" :[{"origin" : cc.p(5,4), "destination" : cc.p(7,8)},
                   {"origin" : cc.p(5,2), "destination" : cc.p(30,4)}]
};

var  AwayPathConfig = {
    "UpPath" : [{"origin" : cc.p(53,12), "destination" : cc.p(55,16)},
                  {"origin" : cc.p(30,16), "destination" : cc.p(55,18)}],
    "MiddlePath" : [{"origin" : cc.p(30,9), "destination" : cc.p(52,11)}],
    "DownPath" : [{"origin" : cc.p(53,4),"destination" : cc.p(55,8)},
                    {"origin" : cc.p(30,2), "destination" : cc.p(55,4)}]
}


/*var isInDownPath = function(point){
    if((2 * TMXTileMapsize) <= point.y && point.y <= (4 * TMXTileMapsize)){
        if((5 * TMXTileMapsize) <= point.x && point.x <= (50*TMXTileMapsize)){
            return true;
        }
    }
    else if((4 * TMXTileMapsize) <= point.y && point.y <= (8 * TMXTileMapsize)){
        if((5 * TMXTileMapsize) <= point.x && point.x <= (7 * TMXTileMapsize)){
            return true;
        }
        else if((52 * TMXTileMapsize) <= point.x && point.x <= (54 * TMXTileMapsize)){
            return true;
        }
    }
    return false;
};

var isInMiddlePath = function(point){
    if((8 * TMXTileMapsize) <= point.x && (51 * TMXTileMapsize)){
        if((9 * TMXTileMapsize) <= point.y && point.y <= (11 * TMXTileMapsize)){
            return true;
        }
    }
    return false;
};

var isInUpPath = function(point){
    if((16 * TMXTileMapsize) <= point.y && point.y <= (18 * TMXTileMapsize)){
        if((5 * TMXTileMapsize) <= point.x && point.x <= (50*TMXTileMapsize)){
            return true;
        }
    }
    else if((13 * TMXTileMapsize) <= point.y && point.y <= (17 * TMXTileMapsize)){
        if((5 * TMXTileMapsize) <= point.x && point.x <= (7 * TMXTileMapsize)){
            return true;
        }
        else if((52 * TMXTileMapsize) <= point.x && point.x <= (54 * TMXTileMapsize)){
            return true;
        }
    }
    return false;
}*/

//建筑物可以放得位置
var BuilddingPosition = {

};