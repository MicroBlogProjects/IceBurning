/**
 * Created by JiaChen on 2016/4/18.
 */

var MusketConfig = MusketConfig || {};

//属性
MusketConfig.attribute = {
    "id" : 4, //id
    "name" : "火枪手",
    "sightRadius" : 3, //视野半径
    "defense" : 20.0,

    "HP" : 120.0, //血量
    "attack" : 40.0, //攻击力
    "attackRadius" : 3, //攻击半径
    "attackSpeed" : 0.5 / GC.AttackSpeedCoefficient,  //攻击速度 多少秒一下
    "walkSpeed" : 20, //移动速度
    "coincost" :20,
    "attackType" : 0,


    "descript" : "拥有精准的射术，配上趁手的火枪，对敌人造成强力的打击",
    "Icon" : res.GM_MusketIcon_png,
    "defaultImage" : res.GM_MusketDefault_png
};

//攻击
MusketConfig.attack = {
    "allTime" :  GC.AttackSpeedCoefficient / 0.5,
    "attackTime" :GC.AttackSpeedCoefficient / 0.5 / 2,
    "begin" : {
        "time" : GC.AttackSpeedCoefficient / 0.5 / 2,
        "account" : 11,
        "prefix" : "MusketAttackBegin",
        "animatePlist" : res.GM_Musket_plist
    },
    "end" : {
        "time" : GC.AttackSpeedCoefficient / 0.5 / 2,
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
        "time" : GC.WalkingSpeedCoefficient / 2,
        "account" : 7,
        "prefix" : "MusketWalking",
        "animatePlist" : res.GM_Musket_plist
    },
    "end" :null
};
