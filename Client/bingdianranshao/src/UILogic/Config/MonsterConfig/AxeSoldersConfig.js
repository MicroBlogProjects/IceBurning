/**
 * Created by JiaChen on 2016/4/18.
 */


var AxeSoldersConfig = AxeSoldersConfig || {};

//属性
AxeSoldersConfig.attribute = {
    "id" : 6, //id
    "name" : "斧兵",

    "walkSpeed" : 50, //移动速度
    "HP" : 1.0, //血量
    "sightRadius" : 100.0, //视野半径
    "defense" : 20.0,
    "attack" : 20.0, //攻击力
    "attackRadius" : 10.0, //攻击半径
    //"attackSpeed" : 1.0  //攻击速度 多少秒一下

    "Icon" : res.GM_AxeSoldiersIcon_png,
    "defaultImage" : res.GM_AxeSoldiersDefault_png
};

//攻击
AxeSoldersConfig.attack = {
    "begin" : {
        "time" : 0.6,
        "account" : 6,
        "prefix" : "AxeSoldiersAttackBegin",
        "animatePlist" : res.GM_AxeSoldiers_plist
    },
    "end" : {
        "time" : 0.6,
        "account" : 6,
        "prefix" : "AxeSoldiersAttackEnd",
        "animatePlist" : res.GM_AxeSoldiers_plist
    }
};

AxeSoldersConfig.death = {
    "begin" : {
        "time" : 0.6,
        "account" : 6,
        "prefix" : "AxeSoldiersDeath",
        "animatePlist" : res.GM_AxeSoldiers_plist
    },
    "end" : null
};

AxeSoldersConfig.skill = null;

AxeSoldersConfig.walking = {
    "begin" :{
        "time" : 0.6,
        "account" : 6,
        "prefix" : "AxeSoldiersWalking",
        "animatePlist" : res.GM_AxeSoldiers_plist
    },
    "end" :null
};