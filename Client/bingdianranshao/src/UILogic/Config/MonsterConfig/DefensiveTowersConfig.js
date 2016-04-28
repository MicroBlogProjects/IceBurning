/**
 * Created by chenjia on 2016/4/24.
 */


var DefensiveTowersConfig = DefensiveTowersConfig || {};

//属性
DefensiveTowersConfig.attribute = {
    "id" : 105, //id
    "name" : "守卫树精",
    "Icon" :res.GM_DefensiveTowersIcon_png,
    "defaultImage" : res.GM_DefensiveTowersDefault_png,
    "sightRadius" : 4, //视野半径
    "defense" : 20.0,

    "HP" : 500.0, //血量
    "attack" : 30, //攻击力
    "attackSpeed" : 0,
    "walkSpeed" : 0, //移动速度
    "attackRadius" : 0, //攻击半径
    "coincost" :80,

    "descript" : "热爱大自然树精卫士，为了抵抗邪恶势力的入侵，进化出唯一一种攻击方式自爆,死亡后对范围内的对方怪物造成一定杀伤"

};

DefensiveTowersConfig.attack = null;

//死亡
DefensiveTowersConfig.death = {
    "attribute" :{
        "attack" : 30,
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