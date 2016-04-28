/**
 * Created by JiaChen on 2016/4/18.
 */

var KnightConfig = KnightConfig || {};

//属性
KnightConfig.attribute = {
    "id" : 2, //id
    "name" : "骑士",

    "walkSpeed" : 10, //移动速度
    "HP" : 200.0, //血量
    "sightRadius" : 3, //视野半径
    "defense" : 20.0,
    "attack" : 30.0, //攻击力
    "attackRadius" : 1, //攻击半径
    "attackSpeed" : 0.5,  //攻击速度 多少秒一下
    "coincost" :20,
    "attackType" : 0,

    "Icon" : res.GM_KnightIcon_png,
    "defaultImage" : res.GM_KnightDefault_png
};

//攻击
KnightConfig.attack = {
    "allTime" : 1.5,
    "attackTime" : 1,
    "begin" : {
        "time" : 1,
        "account" : 20,
        "prefix" : "KnightAttackBegin",
        "animatePlist" : res.GM_Knight_plist
    },
    "end" : {
        "time" :0.5,
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
        "time" : 1,
        "account" : 6,
        "prefix" : "KnightWlking",
        "animatePlist" : res.GM_Knight_plist
    },
    "end" :null
};