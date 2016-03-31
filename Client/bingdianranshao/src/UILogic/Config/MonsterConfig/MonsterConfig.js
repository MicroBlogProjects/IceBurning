/**
 * Created by jiachen on 2016/3/29.
 */

var YuangujurenAttribute = {
    "id" : 1,
    "name" : "远古巨人",
    "speed" : 20,
    "attack" : 20,
    "HP" : 20
};
var YuangujurenAnimate = {
    "prefixName" : "ygjr",
    "defaultImage" : res.GM_Ygjr_png,
    "walkingAnimatePlist" : res.GM_Ygjrwalking_plist,
    "walkingAnimateAccount" : 16,
    "attackAnimatePlist" : res.GM_Ygjrattack_plist,
    "attackAnimateAccount" : 12,
    "deathAnimatePlist" :  res.GM_Ygjrdeath_plist,
    "deathAnimateAccount" : 4
};

var MonsterConfig = {
    "yuangujuren" : {"attribute" : YuangujurenAttribute,
                       "animate" : YuangujurenAnimate}
};



