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

var LAYER_PRIORITY_BACKGROUND = 0;			               //背景层优先级
var LAYER_PRIORITY_MAP = 5;                                //地图优先级
var LAYER_PRIORITY_TOUCH = 100;                                //点击层优先级
var LAYER_PRIORITY_MONSTER = 10;                                //怪物层优先级