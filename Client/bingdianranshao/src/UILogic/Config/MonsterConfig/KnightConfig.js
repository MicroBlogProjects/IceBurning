/**
 * Created by JiaChen on 2016/4/18.
 */

var KnightConfig = KnightConfig || {};

//属性
KnightConfig.attribute = {
    "id" : 2, //id
    "name" : "骑士",

    "HP" : 200.0, //血量
    "attack" : 60.0, //攻击力
    "attackRadius" : 1, //攻击半径
    "attackSpeed" : 0.7 / GC.AttackSpeedCoefficient,  //攻击速度 多少秒一下
    "walkSpeed" : 30, //移动速度
    "coincost" :35,
    "attackType" : 0,
    "sightRadius" : 3, //视野半径
    "defense" : 20.0,

    "descript" :"骑士会用自己的生命，来保护自己的家园，骑士们永远不会背弃自己的家园，即使代价是死亡",
    "Icon" : res.GM_KnightIcon_png,
    "defaultImage" : res.GM_KnightDefault_png
};

//攻击
KnightConfig.attack = {
    "allTime" :  GC.AttackSpeedCoefficient / 0.7,
    "attackTime" : GC.AttackSpeedCoefficient / 0.7 * 0.8,
    "begin" : {
        "time" : GC.AttackSpeedCoefficient / 0.7 * 0.8,
        "account" : 20,
        "prefix" : "KnightAttackBegin",
        "animatePlist" : res.GM_Knight_plist
    },
    "end" : {
        "time" :GC.AttackSpeedCoefficient / 0.7 * 0.2,
        "account" : 6,
        "prefix" : "KnightAttackEnd",
        "animatePlist" : res.GM_Knight_plist
    }
};

KnightConfig.death = {
    "begin" : {
        "time" : 0.4,
        "account" : 4,
        "prefix" : "KnightDeath",
        "animatePlist" : res.GM_Knight_plist
    },
    "end" : null
};

KnightConfig.skill = null;

KnightConfig.walking = {
    "begin" :{
        "time" : 3 / GC.WalkingSpeedCoefficient,
        "account" : 6,
        "prefix" : "KnightWlking",
        "animatePlist" : res.GM_Knight_plist
    },
    "end" :null
};