/**
 * Created by JiaChen on 2016/4/19.
 */


var WolfConfig = WolfConfig || {};

//属性
WolfConfig.attribute = {
    "id" : 10, //id
    "name" : "狼",
    "sightRadius" : 3, //视野半径
    "defense" : 20.0,

    "HP" : 150.0, //血量
    "attack" : 25.0, //攻击力
    "attackRadius" : 1, //攻击半径
    "attackSpeed" : 0.7 / GC.AttackSpeedCoefficient,  //攻击速度 多少秒一下
    "walkSpeed" : 30, //移动速度
    "coincost" :25,
    "attackType" : 0,

    "descript" : "来自草原的野狼，在高速移动中，给与敌人巨大的杀伤",
    "Icon" : res.GM_WolfIcon_png,
    "defaultImage" : res.GM_WolfDefault_png
};

//攻击
WolfConfig.attack = {
    "allTime" :GC.AttackSpeedCoefficient / 0.7,
    "attackTime" : GC.AttackSpeedCoefficient / 0.7,
    "begin" : {
        "time" : GC.AttackSpeedCoefficient / 0.7,
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
        "time" : GC.WalkingSpeedCoefficient / 3,
        "account" : 6,
        "prefix" : "WolfWalking",
        "animatePlist" : res.GM_Wolf_plist
    },
    "end" :null
};
