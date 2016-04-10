/**
 * Created by jiachen on 2016/4/8.
 */

var YuangujurenConfig = YuangujurenConfig || {};

//属性
YuangujurenConfig.attribute = {
    "id" : 1, //id
    "name" : "远古巨人",
    "walkSpeed" : 50, //移动速度
    "HP" : 20.0, //血量
    "sightRadius" : 100.0, //视野半径
    "defense" : 20.0,

    "attack" : 20.0, //攻击力
    "attackRadius" : 5.0, //攻击半径
    //"attackSpeed" : 1.0  //攻击速度 多少秒一下

    "Icon" : res.GM_YgjrIcon_png,
    "defaultImage" : res.GM_Ygjr_png
};

//攻击
YuangujurenConfig.attack = {
    "begin" : {
        "time" : 1,
        "account" : 12,
        "prefix" : "ygjrattack",
        "animatePlist" : res.GM_Ygjrattack_plist
    },
    "end" : null
};

YuangujurenConfig.death = {
    "begin" : {
        "time" : 0.5,
        "account" : 4,
        "prefix" : "ygjrdeath",
        "animatePlist" : res.GM_Ygjrdeath_plist
    },
    "end" : null
};

YuangujurenConfig.walking = {
    "begin" :{
        "time" : 2,
        "account" : 16,
        "prefix" : "ygjrwalking",
        "animatePlist" : res.GM_Ygjrwalking_plist
    },
    "end" :null
};

YuangujurenConfig.skill = null;







/*var YuangujurenAnimate = {
    "prefixName" : "ygjr",
    "walkingAnimatePlist" : res.GM_Ygjrwalking_plist,
    "walkingAnimateAccount" : 16,
    "attackAnimatePlist" : res.GM_Ygjrattack_plist,
    "attackAnimateAccount" : 12,
    "deathAnimatePlist" :  res.GM_Ygjrdeath_plist,
    "deathAnimateAccount" : 4
};


var YuanGujurenConfig = {
    "attribute" : YuangujurenAttribute,
    "animate" : YuangujurenAnimate,
    "defaultImage" : res.GM_Ygjr_png,
    //"skill" : null
};

var attackAttribute = {
    "time" : 1,
    "account" : 12,
    "prefix" : "ygjrattack",
    "attackAnimatePlist" : res.GM_Ygjrattack_plist
};

var attackAnimate = {
    "attackAnimatePlist" : res.GM_Ygjrattack_plist
};

var attackConfig ={
    "atttibute" : attackAttribute,
    "animte" : attackAnimate
}

var walkingAttribute = {
    "time" : 2,
    "account" : 16,
    "prefix" : "ygjrwalking"
    "walkingAnimatePlist" : res.GM_Ygjrwalking_plist
};

var walkingAnimate = {
    "walkingAnimatePlist" : res.GM_Ygjrwalking_plist
};

var walkingCofig = {
    "attribute" : walkingAttribute,
    "animate" : walkingAnimate
}

var deathAttribute = {
    "time" : 0.5,
    "account" : 4,
    "prefix" : "ygjrdeath"
};

var deathAnimate = {
    "deathAnimatePlist" : res.GM_Ygjrdeath_plist
}

var deathConfig = {
    "attribute" : deathAttribute,
    "animate" : deathAnimate
};*/




