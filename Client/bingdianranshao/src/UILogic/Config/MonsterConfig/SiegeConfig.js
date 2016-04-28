/**
 * Created by chenjia on 2016/4/24.
 */

var SiegeConfig = SiegeConfig || {};

//属性
SiegeConfig.attribute = {
    "id" : 11, //id
    "name" : "毁灭战士",
    "sightRadius" : 3, //视野半径
    "defense" : 20.0,

    "HP" : 250, //血量
    "attack" : 100.0, //攻击力
    "attackRadius" : 1, //攻击半径
    "attackSpeed" : 0.5 / GC.AttackSpeedCoefficient,  //攻击速度 多少秒一下
    "walkSpeed" : 10, //移动速度
    "coincost" :40,
    "attackType" : 0,

    "descript" : "肩抗巨大的木头，拥有毁灭一切的力量，藐视任何敌人，对于建筑物毁灭性打击",
    "Icon" : res.GM_SiegeIcon_png,
    "defaultImage" : res.GM_SiegeDefault_png
};

//攻击
SiegeConfig.attack = {
    "allTime" :   GC.AttackSpeedCoefficient / 0.5,
    "attackTime" : GC.AttackSpeedCoefficient / 0.5,
    "begin" : {
        "time" : GC.AttackSpeedCoefficient / 0.5,
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
        "time" : GC.WalkingSpeedCoefficient / 1,
        "account" : 6,
        "prefix" : "SiegeWalking",
        "animatePlist" : res.GM_Siege_plist
    },
    "end" :null
};
