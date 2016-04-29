/**
 * Created by JiaChen on 2016/4/18.
 */

var LongSwordConfig = LongSwordConfig || {};

//属性
LongSwordConfig.attribute = {
    "id" : 3, //id
    "name" : "长刀兵",
    "sightRadius" : 3, //视野半径
    "defense" : 20.0,


    "HP" : 100.0, //血量
    "attack" : 20.0, //攻击力
    "attackRadius" : 1, //攻击半径
    "attackSpeed" : 1.0 / GC.AttackSpeedCoefficient,  //攻击速度 多少秒一下
    "walkSpeed" : 20, //移动速度
    "coincost" :10,
    "attackType" : 0,

    "descript" : "守卫军中最基本的单位，攻守平衡",
    "Icon" : res.GM_LongSwordIcon_png,
    "defaultImage" : res.GM_LongSwordDefault_png
};

//攻击
LongSwordConfig.attack = {
    "allTime" :  GC.AttackSpeedCoefficient / 1,
    "attackTime" :  GC.AttackSpeedCoefficient / 1,
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
        "time" : GC.WalkingSpeedCoefficient /2,
        "account" : 6,
        "prefix" : "LongSwordWalking",
        "animatePlist" : res.GM_LongSword_plist
    },
    "end" :null
};