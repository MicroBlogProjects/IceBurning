/**
 * Created by JiaChen on 2016/4/18.
 */

var MusketConfig = MusketConfig || {};

//属性
MusketConfig.attribute = {
    "id" : 4, //id
    "name" : "火枪兵",

    "walkSpeed" : 10, //移动速度
    "HP" : 120.0, //血量
    "sightRadius" : 3, //视野半径
    "defense" : 20.0,
    "attack" : 40.0, //攻击力
    "attackRadius" : 3, //攻击半径
    "attackSpeed" : 0.7,  //攻击速度 多少秒一下
    "coincost" :20,
    "attackType" : 0,

    "Icon" : res.GM_MusketIcon_png,
    "defaultImage" : res.GM_MusketDefault_png
};

//攻击
MusketConfig.attack = {
    "allTime" : 1.4,
    "attackTime" : 0.7,
    "begin" : {
        "time" : 0.7,
        "account" : 11,
        "prefix" : "MusketAttackBegin",
        "animatePlist" : res.GM_Musket_plist
    },
    "end" : {
        "time" : 0.7,
        "account" : 11,
        "prefix" : "MusketAttackEnd",
        "animatePlist" : res.GM_Musket_plist
    }
};

MusketConfig.death = {
    "begin" : {
        "time" : 0.6,
        "account" : 6,
        "prefix" : "MusketDeath",
        "animatePlist" : res.GM_Musket_plist
    },
    "end" : null
};

MusketConfig.skill = null;

MusketConfig.walking = {
    "begin" :{
        "time" : 1,
        "account" : 7,
        "prefix" : "MusketWalking",
        "animatePlist" : res.GM_Musket_plist
    },
    "end" :null
};
