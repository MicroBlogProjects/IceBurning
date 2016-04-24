/**
 * Created by chenjia on 2016/4/24.
 */

var SiegeConfig = SiegeConfig || {};

//属性
SiegeConfig.attribute = {
    "id" : 11, //id
    "name" : "攻城兵",

    "walkSpeed" : 50, //移动速度
    "HP" : 10.0, //血量
    "sightRadius" : 3, //视野半径
    "defense" : 20.0,
    "attack" : 20.0, //攻击力
    "attackRadius" : 1, //攻击半径
    "attackSpeed" : 1.0,  //攻击速度 多少秒一下

    "Icon" : res.GM_SiegeIcon_png,
    "defaultImage" : res.GM_SiegeDefault_png
};

//攻击
SiegeConfig.attack = {
    "begin" : {
        "time" : 1,
        "account" : 10,
        "prefix" : "SiegeAttackBegin",
        "animatePlist" : res.GM_Siege_plist
    },
    "end" : null
};

SiegeConfig.death = {
    "begin" : {
        "time" : 0.6,
        "account" : 6,
        "prefix" : "SiegeDeath",
        "animatePlist" : res.GM_Siege_plist
    },
    "end" : null
};

SiegeConfig.skill = null;

SiegeConfig.walking = {
    "begin" :{
        "time" : 1.2,
        "account" : 12,
        "prefix" : "SiegeWalking",
        "animatePlist" : res.GM_Siege_plist
    },
    "end" :null
};
