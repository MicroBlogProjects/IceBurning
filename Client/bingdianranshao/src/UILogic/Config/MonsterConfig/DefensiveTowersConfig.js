/**
 * Created by chenjia on 2016/4/24.
 */


var DefensiveTowersConfig = DefensiveTowersConfig || {};

//属性
DefensiveTowersConfig.attribute = {
    "id" : 105, //id
    "name" : "自爆塔",
    "Icon" :res.GM_DefensiveTowersIcon_png,
    "defaultImage" : res.GM_DefensiveTowersDefault_png,

    "walkSpeed" : 0, //移动速度
    "HP" : 20.0, //血量
    "sightRadius" : 4, //视野半径
    "defense" : 20.0,
    "attack" : 20.0, //攻击力
    "attackRadius" : 4, //攻击半径
    "attackSpeed" : 2

};

DefensiveTowersConfig.attack = null;

//死亡
DefensiveTowersConfig.death = {
    "attribute" :{
        "attack" : 20,
        "attackRadius" : 3
    },
    "begin" : {
        "time" : 0.5,
        "account" : 5,
        "prefix" : "DefensiveTowersDeath",
        "animatePlist" : res.GM_DefensiveTowers_plist
    },
    "end" : null
};

//行走
DefensiveTowersConfig.walking = null;

//技能
DefensiveTowersConfig.skill = null