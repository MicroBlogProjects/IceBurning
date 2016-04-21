/**
 * Created by JiaChen on 2016/4/19.
 */


var WizardConfig = WizardConfig || {};


//属性
WizardConfig.attribute = {
    "id" : 9, //id
    "name" : "巫师",

    "walkSpeed" : 20, //移动速度
    "HP" : 10.0, //血量
    "sightRadius" : 2, //视野半径
    "defense" : 20.0,
    "attack" : 20.0, //攻击力
    "attackRadius" : 1, //攻击半径
    "attackSpeed" : 2,

    "Icon" :res.GM_WizardIcon_png,
    "defaultImage" : res.GM_WizardDefault_png
};
//攻击
WizardConfig.attack =  {
    "begin" : {
        "time" : 0.6,
        "account" : 6,
        "prefix" : "WizardAttackBegin",
        "animatePlist" : res.GM_Wizard_plist
    },
    "end" : {
        "time" : 0.2,
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
        "time" : 1.2,
        "account" : 12,
        "prefix" : "WizardWalking",
        "animatePlist" : res.GM_Wizard_plist
    },
    "end" : null
};

WizardConfig.skill = {
    "attribute" : {
        "offsetPoint" : cc.p(0,0),
        "isRangeAttack" : false,
        "isArcAnimate" : false,
        "attack" : 20, //有技能伤害 则伤害根据技能伤害算
        "time" : 0.2,
        "attackRadius" :1,
        "defaultImage" : res.GM_WizardSkill_png
    },
    "Animate" : null
};

