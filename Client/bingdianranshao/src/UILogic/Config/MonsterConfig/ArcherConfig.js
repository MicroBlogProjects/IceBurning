/**
 * Created by JiaChen on 2016/4/19.
 */

var ArcherConfig = ArcherConfig || {};


//属性
ArcherConfig.attribute = {
    "id" : 7, //id
    "name" : "弓箭手",


    "walkSpeed" : 20, //移动速度
    "HP" : 60.0, //血量
    "defense" : 20.0,
    "attack" : 30.0, //攻击力
    "attackRadius" : 2, //攻击半径
    "attackSpeed" : 2,
    "coincost" :10,

    "Icon" :res.GM_ArcherIcon_png,
    "defaultImage" : res.GM_ArcherDefault_png
};
//攻击
ArcherConfig.attack =  {
    "allTime" : 1.3,
    "attackTime" : 1.5,
    "begin" : {
        "time" : 1.3,
        "account" : 9,
        "prefix" : "ArcherAttackBegin",
        "animatePlist" : res.GM_Archer_plist
    },
    "end" : null
};

//死亡
ArcherConfig.death = {
    "allTime" : 0.7,
    "attackTime" : 0.9,
    "begin" : {
        "time" : 0.7,
        "account" : 7,
        "prefix" : "ArcherDeath",
        "animatePlist" : res.GM_Archer_plist
    },
    "end" : null
};

//行走
ArcherConfig.walking = {
    "begin" : {
        "time" : 1,
        "account" : 6,
        "prefix" : "ArcherWalking",
        "animatePlist" : res.GM_Archer_plist
    },
    "end" : null
};

ArcherConfig.skill = {
    "attribute" : {
        "offsetPoint" : cc.p(0,0),
        "isRangeAttack" : false,
        "isArcAnimate" : MonsterAnimateKind.StraightAnimate,
        "attack" : 20, //有技能伤害 则伤害根据技能伤害算
        "time" : 0.2,
        "attackRadius" :1,
        "defaultImage" : res.GM_ArcherSkillDefault_png
    },
    "Animate" : null
}

