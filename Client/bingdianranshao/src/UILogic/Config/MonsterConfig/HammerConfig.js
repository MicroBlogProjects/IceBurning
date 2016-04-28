/**
 * Created by JiaChen on 2016/4/19.
 */

var HammerConfig = HammerConfig || {};

//属性
HammerConfig.attribute = {
    "id" : 8, //id
    "name" : "战锤",

    "HP" : 200.0, //血量
    "attack" : 25.0, //攻击力
    "attackRadius" : 1, //攻击半径
    "attackSpeed" : 0.5 / GC.AttackSpeedCoefficient,  //攻击速度 多少秒一下
    "walkSpeed" : 20, //移动速度
    "sightRadius" : 2, //视野半径
    "defense" : 20.0,
    "coincost" :35,

    "attackType" : 1,

    "descript" : "拥有野蛮人血脉的战锤，手持巨大的战锤，对于面前范围内的敌人，给与巨大的打击",
    "Icon" : res.GM_HammerIcon_png,
    "defaultImage" : res.GM_HammerDefault_png
};

//攻击
HammerConfig.attack = {
    "allTime" : GC.AttackSpeedCoefficient / 0.5,
    "attackTime" :GC.AttackSpeedCoefficient / 0.5* 0.6,
    "begin" : {
        "time" : GC.AttackSpeedCoefficient / 0.5* 0.6,
        "account" : 10,
        "prefix" : "HammerAttackBegin",
        "animatePlist" : res.GM_Hammer_plist
    },
    "end" : {
        "time" : GC.AttackSpeedCoefficient / 0.5* 0.4,
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
        "time" : 2 / GC.WalkingSpeedCoefficient,
        "account" : 6,
        "prefix" : "HummerWalking",
        "animatePlist" : res.GM_Hammer_plist
    },
    "end" :null
};
