/**
 * Created by JiaChen on 2016/4/18.
 */


var AxeSoldersConfig = AxeSoldersConfig || {};

//属性
AxeSoldersConfig.attribute = {
    "id" : 6, //id
    "name" : "斧兵",

    "walkSpeed" : 10, //移动速度
    "HP" : 200.0, //血量
    "sightRadius" : 3, //视野半径
    "defense" : 20.0,
    "attack" : 70.0, //攻击力
    "attackRadius" : 0.5, //攻击半径
    "attackSpeed" : 1.0,  //攻击速度 多少秒一下
    "coincost" :30,

    "attackType" : 0,

    "Icon" : res.GM_AxeSoldiersIcon_png,
    "defaultImage" : res.GM_AxeSoldiersDefault_png
};

//攻击
AxeSoldersConfig.attack = {
    "allTime" : 1,
    "attackTime" : 0.5,
    "begin" : {
        "time" : 0.5,
        "account" : 6,
        "prefix" : "AxeSoldiersAttackBegin",
        "animatePlist" : res.GM_AxeSoldiers_plist
    },
    "end" : {
        "time" : 0.5,
        "account" : 6,
        "prefix" : "AxeSoldiersAttackEnd",
        "animatePlist" : res.GM_AxeSoldiers_plist
    }
};

AxeSoldersConfig.death = {
    "allTime" : 0.6,
    "attackTime" : 0.6,
    "begin" : {
        "time" : 0.6,
        "account" : 6,
        "prefix" : "AxeSoldiersDeath",
        "animatePlist" : res.GM_AxeSoldiers_plist
    },
    "end" : null
};

AxeSoldersConfig.skill = null;

AxeSoldersConfig.walking = {
    "begin" :{
        "time" : 2,
        "account" : 6,
        "prefix" : "AxeSoldiersWalking",
        "animatePlist" : res.GM_AxeSoldiers_plist
    },
    "end" :null
};