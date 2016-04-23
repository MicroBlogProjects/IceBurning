/**
 * Created by jiachen on 2016/4/22.
 */

var TowersConfig = TowersConfig || {};


//属性
TowersConfig.attribute = {
    "id" : 104, //id
    "name" : "箭塔",

    "walkSpeed" : 0, //移动速度
    "HP" : 100.0, //血量
    "sightRadius" : 3, //视野半径
    "defense" : 20.0,
    "attack" : 20.0, //攻击力
    "attackRadius" : 2, //攻击半径
    "attackSpeed" : 2,

    "Icon" :res.GM_TowersIcon_png,
    "defaultImage" : res.GM_TowersDefault_png
};
//攻击
TowersConfig.attack =  {
    "begin" : {
        "time" : 2,
        "account" : 1,
        "prefix" : "TowersAttackBegin",
        "animatePlist" : res.GM_Towers_plist
    },
    "end" : null
};

//死亡
TowersConfig.death = {
    "begin" : {
        "time" : 2,
        "account" : 7,
        "prefix" : "xxmftdeath",
        "animatePlist" : res.GM_XxmftDeath_Plist
    },
    "end" : null
};

//行走
TowersConfig.walking = null;


TowersConfig.skill = {
    "attribute" : {
        "offsetPoint" : cc.p(0,50),
        "isRangeAttack" : false,
        "isArcAnimate" : MonsterAnimateKind.StraightAnimate,
        "attack" : 20, //有技能伤害 则伤害根据技能伤害算
        "time" : 0.2,
        "attackRadius" :1,
        "defaultImage" : res.GM_TowersSkill_png
    },
    "Animate" : null
};
