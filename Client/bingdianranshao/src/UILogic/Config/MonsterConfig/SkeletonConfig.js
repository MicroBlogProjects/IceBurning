/**
 * Created by JiaChen on 2016/4/18.
 */

var SkeletonConfig = SkeletonConfig || {};

//属性
SkeletonConfig.attribute = {
    "id" : 5, //id
    "name" : "骷髅兵",

    "walkSpeed" : 50, //移动速度
    "HP" : 1.0, //血量
    "sightRadius" : 100.0, //视野半径
    "defense" : 20.0,
    "attack" : 20.0, //攻击力
    "attackRadius" : 10.0, //攻击半径
    "attackSpeed" : 1.0,  //攻击速度 多少秒一下

    "Icon" : res.GM_SkeletonIcon_png,
    "defaultImage" : res.GM_SkeletonDefault_png
};

//攻击
SkeletonConfig.attack = {
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
        "time" : 0.8,
        "account" : 8,
        "prefix" : "SkeletonWalking",
        "animatePlist" : res.GM_Skeleton_plist
    },
    "end" :null
};
