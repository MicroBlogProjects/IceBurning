/**
 * Created by JiaChen on 2016/4/19.
 */


var WolfConfig = WolfConfig || {};

//属性
WolfConfig.attribute = {
    "id" : 10, //id
    "name" : "狼",

    "walkSpeed" : 50, //移动速度
    "HP" : 1.0, //血量
    "sightRadius" : 3, //视野半径
    "defense" : 20.0,
    "attack" : 20.0, //攻击力
    "attackRadius" : 1, //攻击半径
    "attackSpeed" : 1.0,  //攻击速度 多少秒一下
    "coincost" :20,

    "Icon" : res.GM_WolfIcon_png,
    "defaultImage" : res.GM_WolfDefault_png
};

//攻击
WolfConfig.attack = {
    "allTime" :1,
    "attackTime" : 1,
    "begin" : {
        "time" : 1,
        "account" : 10,
        "prefix" : "WolfAttack",
        "animatePlist" : res.GM_Wolf_plist
    },
    "end" : null
};

WolfConfig.death = {
    "begin" : {
        "time" : 0.8,
        "account" : 8,
        "prefix" : "WolfDeath",
        "animatePlist" : res.GM_Wolf_plist
    },
    "end" : null
};

WolfConfig.skill = null;

WolfConfig.walking = {
    "begin" :{
        "time" : 0.8,
        "account" : 8,
        "prefix" : "WolfWalking",
        "animatePlist" : res.GM_Wolf_plist
    },
    "end" :null
};
