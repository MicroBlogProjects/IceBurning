/**
 * Created by JiaChen on 2016/4/19.
 */

var HammerConfig = HammerConfig || {};

//属性
HammerConfig.attribute = {
    "id" : 8, //id
    "name" : "锤兵",

    "walkSpeed" : 50, //移动速度
    "HP" : 1.0, //血量
    "sightRadius" : 2, //视野半径
    "defense" : 20.0,
    "attack" : 20.0, //攻击力
    "attackRadius" : 2, //攻击半径
    "attackSpeed" : 1.0,  //攻击速度 多少秒一下
    "coincost" :20,

    "Icon" : res.GM_HammerIcon_png,
    "defaultImage" : res.GM_HammerDefault_png
};

//攻击
HammerConfig.attack = {
    "allTime" : 1.4,
    "attackTime" : 1,
    "begin" : {
        "time" : 1,
        "account" : 10,
        "prefix" : "HammerAttackBegin",
        "animatePlist" : res.GM_Hammer_plist
    },
    "end" : {
        "time" : 0.4,
        "account" : 4,
        "prefix" : "HammerAttackEnd",
        "animatePlist" : res.GM_Hammer_plist
    }
};

HammerConfig.death = {
    "begin" : {
        "time" : 0.7,
        "account" : 7,
        "prefix" : "HammerDeath",
        "animatePlist" : res.GM_Hammer_plist
    },
    "end" : null
};

HammerConfig.skill = null;

HammerConfig.walking = {
    "begin" :{
        "time" : 0.6,
        "account" : 6,
        "prefix" : "HummerWalking",
        "animatePlist" : res.GM_Hammer_plist
    },
    "end" :null
};
