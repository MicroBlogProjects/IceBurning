/**
 * Created by JiaChen on 2016/4/19.
 */

var ArcherConfig = ArcherConfig || {};


//属性
ArcherConfig.attribute = {
    "id" : 7, //id
    "name" : "丛林猎手",
    "defense" : 20.0,
    "sightRadius" : 3, //视野半径


    "HP" : 60.0, //血量
    "attack" : 30.0, //攻击力
    "attackRadius" : 2, //攻击半径
    "attackSpeed" : 1.5/GC.AttackSpeedCoefficient,
    "walkSpeed" : 20, //移动速度
    "coincost" :10,
    "attackType" : 0,

    "descript" : "擅长使用弓箭，在后方进行远距离攻击。凭借快速的移动和攻速令敌人胆寒",
    "Icon" :res.GM_ArcherIcon_png,
    "defaultImage" : res.GM_ArcherDefault_png
};
//攻击
ArcherConfig.attack =  {
    "allTime" :GC.AttackSpeedCoefficient/1.5,
    "attackTime" : GC.AttackSpeedCoefficient/1.5 - 0.3,
    "begin" : {
        "time" : GC.AttackSpeedCoefficient/1.5 - 0.3,
        "account" : 9,
        "prefix" : "ArcherAttackBegin",
        "animatePlist" : res.GM_Archer_plist
    },
    "end" : {
        "time" : 0.3,
        "account" : 1,
        "prefix" : "ArcherAttackBegin",
        "animatePlist" : res.GM_Archer_plist
    }
};

//死亡
ArcherConfig.death = {
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
        "time" : GC.WalkingSpeedCoefficient /2,
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

