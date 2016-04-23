/**
 * Created by jiachen on 2016/4/21.
 */

var MainCityConfig = MainCityConfig || {};


//属性
MainCityConfig.attribute = {
    "id" : 201, //id
    "name" : "主城",

    "walkSpeed" : 0, //移动速度
    "HP" : 100.0, //血量
    "sightRadius" : 0, //视野半径
    "defense" : 20.0,
    "attack" : 0.0, //攻击力
    "attackRadius" : 0, //攻击半径
    "attackSpeed" : 0,

    "Icon" :res.GM_XxmftIcon_Png,
    "defaultImage" : res.GM_MainCity_png
};

MainCityConfig.waling = null;

MainCityConfig.attack = null;

MainCityConfig.skill = null;
