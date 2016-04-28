/**
 * Created by JiaChen on 2016/4/18.
 */

var LongSwordConfig = LongSwordConfig || {};

//属性
LongSwordConfig.attribute = {
    "id" : 3, //id
    "name" : "长刀兵",

    "walkSpeed" : 20, //移动速度
    "HP" : 60.0, //血量
    "sightRadius" : 3, //视野半径
    "defense" : 20.0,
    "attack" : 20.0, //攻击力
    "attackRadius" : 2, //攻击半径
    "attackSpeed" : 1.0,  //攻击速度 多少秒一下
    "coincost" :5,

    "Icon" : res.GM_LongSwordIcon_png,
    "defaultImage" : res.GM_LongSwordDefault_png
};

//攻击
LongSwordConfig.attack = {
    "allTime" : 1,
    "attackTime" : 1,
    "begin" : {
        "time" : 1,
        "account" : 11,
        "prefix" : "LongSwordAttackBegin",
        "animatePlist" : res.GM_LongSword_plist
    },
    "end" : null
};

LongSwordConfig.death = {
    "begin" : {
        "time" : 0.5,
        "account" : 5,
        "prefix" : "LongSwordDeath",
        "animatePlist" : res.GM_LongSword_plist
    },
    "end" : null
};

LongSwordConfig.skill = null;

LongSwordConfig.walking = {
    "begin" :{
        "time" : 0.5,
        "account" : 6,
        "prefix" : "LongSwordWalking",
        "animatePlist" : res.GM_LongSword_plist
    },
    "end" :null
};