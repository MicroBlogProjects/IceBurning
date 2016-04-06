/**
 * Created by jiachen on 2016/3/29.
 */



var MianCityAttribute = {
    "id" : 100, //id
    "name" : "主城",
    "walkSpeed" : 0, //移动速度
    "HP" : 200.0, //血量
    "sightRadius" : 100.0, //视野半径
    "defense" : 20.0,

    "attack" : 20.0, //攻击力
    "attackRadius" : 5.0, //攻击半径
    "attackSpeed" : 1.0  //攻击速度 多少秒一下
};


var YuangujurenAttribute = {
    "id" : 1, //id
    "name" : "远古巨人",
    "walkSpeed" : 20, //移动速度 多少秒一步
    "HP" : 20.0, //血量
    "sightRadius" : 100.0, //视野半径
    "defense" : 20.0,

    "attack" : 20.0, //攻击力
    "attackRadius" : 5.0, //攻击半径
    "attackSpeed" : 1.0  //攻击速度 多少秒一下
};

var YuangujurenAnimate = {
    "prefixName" : "ygjr",
    "walkingAnimatePlist" : res.GM_Ygjrwalking_plist,
    "walkingAnimateAccount" : 16,
    "attackAnimatePlist" : res.GM_Ygjrattack_plist,
    "attackAnimateAccount" : 12,
    "deathAnimatePlist" :  res.GM_Ygjrdeath_plist,
    "deathAnimateAccount" : 4
};

var MonsterConfig = {
    "yuangujuren" : {"attribute" : YuangujurenAttribute,
                       "animate" : YuangujurenAnimate,
                       "defaultImage" : res.GM_Ygjr_png},

    "maincity" : {"attribute" : MianCityAttribute,
                    "animate" : YuangujurenAnimate,
                    "defaultImage" : res.GM_MainCity_png}
};





