/**
 * Created by JiaChen on 2016/4/18.
 */

var SkeletonConfig = SkeletonConfig || {};

//属性
SkeletonConfig.attribute = {
    "id" : 5, //id
    "name" : "骷髅兵",
    "sightRadius" : 3, //视野半径
    "defense" : 20.0,

    "HP" : 150.0, //血量
    "attack" : 50.0, //攻击力
    "attackRadius" : 1, //攻击半径
    "attackSpeed" : 1.0/GC.AttackSpeedCoefficient,  //攻击速度 多少秒一下
    "walkSpeed" : 30, //移动速度
    "coincost" :30,
    "attackType" : 0,

    "descript" :"他曾经是一个保家卫国的高贵骑士，然而不幸被投入地狱，经历了数世纪的折磨,将这具腐烂的躯体连同他麻木的灵魂一起抛回尘世",
    "Icon" : res.GM_SkeletonIcon_png,
    "defaultImage" : res.GM_SkeletonDefault_png
};

//攻击
SkeletonConfig.attack = {
    "allTime" : GC.AttackSpeedCoefficient / 1,
    "attackTime" : GC.AttackSpeedCoefficient / 1,
    "begin" : {
        "time" : 1,
        "account" : 10,
        "prefix" : "SkeletonAttack",
        "animatePlist" : res.GM_Skeleton_plist
    },
    "end" : null
};

SkeletonConfig.death = {
    "begin" : {
        "time" : 0.9,
        "account" : 9,
        "prefix" : "SkeletonDeath",
        "animatePlist" : res.GM_Skeleton_plist
    },
    "end" : null
};

SkeletonConfig.skill = null;

SkeletonConfig.walking = {
    "begin" :{
        "time" : GC.WalkingSpeedCoefficient / 3,
        "account" : 6,
        "prefix" : "SkeletonWalking",
        "animatePlist" : res.GM_Skeleton_plist
    },
    "end" :null
};
