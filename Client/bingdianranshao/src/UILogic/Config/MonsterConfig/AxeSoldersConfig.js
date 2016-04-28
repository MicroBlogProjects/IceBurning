/**
 * Created by JiaChen on 2016/4/18.
 */


var AxeSoldersConfig = AxeSoldersConfig || {};

//属性
AxeSoldersConfig.attribute = {
    "id" : 6, //id
    "name" : "诺玛斧兵",
    "sightRadius" : 3, //视野半径
    "defense" : 20.0,

    "HP" : 200.0, //血量
    "attack" : 70.0, //攻击力
    "attackRadius" : 1, //攻击半径
    "attackSpeed" : 0.5 / GC.AttackSpeedCoefficient,  //攻击速度 多少秒一下
    "walkSpeed" : 10, //移动速度
    "coincost" :50,
    "attackType" : 0,

    "descript" : "装备精良，身着诺玛族工匠特制的重型盔甲，手持染血的战斧，拥有可怕的攻击力和防御力",
    "Icon" : res.GM_AxeSoldiersIcon_png,
    "defaultImage" : res.GM_AxeSoldiersDefault_png
};

//攻击
AxeSoldersConfig.attack = {
    "allTime" :   GC.AttackSpeedCoefficient / 0.5,
    "attackTime" : GC.AttackSpeedCoefficient / 0.5 / 2,
    "begin" : {
        "time" :  GC.AttackSpeedCoefficient / 0.5 /2,
        "account" : 6,
        "prefix" : "AxeSoldiersAttackBegin",
        "animatePlist" : res.GM_AxeSoldiers_plist
    },
    "end" : {
        "time" :  GC.AttackSpeedCoefficient / 0.5 / 2,
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
        "time" : GC.WalkingSpeedCoefficient / 1,
        "account" : 6,
        "prefix" : "AxeSoldiersWalking",
        "animatePlist" : res.GM_AxeSoldiers_plist
    },
    "end" :null
};