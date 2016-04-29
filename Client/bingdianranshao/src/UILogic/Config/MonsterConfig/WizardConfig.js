/**
 * Created by JiaChen on 2016/4/19.
 */


var WizardConfig = WizardConfig || {};


//属性
WizardConfig.attribute = {
    "id" : 9, //id
    "name" : "巫师",
    "sightRadius" : 3, //视野半径
    "defense" : 20.0,

    "HP" : 120.0, //血量
    "attack" : 45, //攻击力
    "attackRadius" : 2, //攻击半径
    "attackSpeed" : 1 / GC.AttackSpeedCoefficient,
    "walkSpeed" : 20, //移动速度
    "coincost" :30,
    "attackType" : 0,

    "descript" : "拥有另外眼花缭乱的魔法，并且利用魔法，给与敌人打击",
    "Icon" :res.GM_WizardIcon_png,
    "defaultImage" : res.GM_WizardDefault_png
};
//攻击
WizardConfig.attack =  {
    "allTime" :GC.AttackSpeedCoefficient / 1 ,
    "attackTime" : GC.AttackSpeedCoefficient / 1 - 0.3,
    "begin" : {
        "time" : GC.AttackSpeedCoefficient / 1 - 0.3,
        "account" : 6,
        "prefix" : "WizardAttackBegin",
        "animatePlist" : res.GM_Wizard_plist
    },
    "end" : {
        "time" : 0.3,
        "account" : 2,
        "prefix" : "WizardAttackEnd",
        "animatePlist" : res.GM_Wizard_plist
    }
};

//死亡
WizardConfig.death = {
    "begin" : {
        "offsetPoint" : cc.p(0,0),
        "time" : 0.7,
        "account" : 7,
        "prefix" : "WizardDeath",
        "animatePlist" : res.GM_Wizard_plist
    },
    "end" : null
};

//行走
WizardConfig.walking = {
    "begin" : {
        "time" : GC.WalkingSpeedCoefficient / 2,
        "account" : 6,
        "prefix" : "WizardWalking",
        "animatePlist" : res.GM_Wizard_plist
    },
    "end" : null
};

WizardConfig.skill = {
    "attribute" : {
        "offsetPoint" : cc.p(0,0),
        "isRangeAttack" : false,
        "isArcAnimate" : MonsterAnimateKind.StraightAnimate,
        "attack" : 20, //有技能伤害 则伤害根据技能伤害算
        "time" : 0.2,
        "attackRadius" :1,
        "defaultImage" : res.GM_WizardSkill_png
    },
    "Animate" : null
};

