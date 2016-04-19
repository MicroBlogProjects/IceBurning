/**
 * Created by jiachen on 2016/4/8.
 */

var XingxingmofataConfig = XingxingmofataConfig || {};


//属性
XingxingmofataConfig.attribute = {
    "id" : 101, //id
    "name" : "星星魔法塔",

    "walkSpeed" : 0, //移动速度
    "HP" : 100.0, //血量
    "sightRadius" : 200.0, //视野半径
    "defense" : 20.0,
    "attack" : 20.0, //攻击力
    "attackRadius" : 200.0, //攻击半径

    "Icon" :res.GM_XxmftIcon_Png,
    "defaultImage" : res.GM_Xxmft_Png
};
//攻击
XingxingmofataConfig.attack =  {
    "begin" : {
        "time" : 1,
        "account" : 10,
        "prefix" : "xxfmtAttack",
        "animatePlist" : res.GM_XxmftAttack_Plist
    },
    "end" : null
    /*"end" : {
        "time" : 1,
        "account" : 9,
        "prefix" : "xxmftattackdeath",
        "animatePlist" : res.GM_XxmftAttackDeath_Plist
    }*/
};

//死亡
XingxingmofataConfig.death = {
    "begin" : {
        "time" : 2,
        "account" : 7,
        "prefix" : "xxmftdeath",
        "animatePlist" : res.GM_XxmftDeath_Plist
    },
    "end" : null
};

//行走
XingxingmofataConfig.walking = null;

//技能
/*XingxingmofataConfig.skill = {
    "attribute" : {
        "attack" : 20,
        "walkingSpeed" : 0,
        "attackRadius" : 5,
        "defaultImage" : res.GM_XxmftSkill_Png
    },
    "attack" :{
        "begin" :{
            "time" : 0.5,
            "account" : 6,
            "prefix" : "attack",
            "animatePlist" : res.GM_XxmftSkillAttack_Plist
        },
        "end" : null
    }
};*/
XingxingmofataConfig.skill = {
    "attribute" : {
        "isRangeAttack" : false,
        "isArcAnimate" : false,
        "attack" : 20, //有技能伤害 则伤害根据技能伤害算
        "time" : 0.2,
        "attackRadius" :1,
        "defaultImage" : res.GM_XxmftSkillArrow_png
    },
    "Animate" : null
}
