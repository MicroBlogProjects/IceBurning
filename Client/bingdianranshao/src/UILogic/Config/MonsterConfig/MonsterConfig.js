/**
 * Created by jiachen on 2016/3/29.
 */

var MonsterType ={
    OwnMonster : 0,
    EnemyMonster : 1
};

var MonsterStep = 20; //一步20

var MonsterState ={
    WalkingLeft :0,
    WalkingRight : 1,
    AttackLeft : 2,
    AttackRight : 3,
    Death : 4
}

var YuangujurenAttribute = {
    "id" : 1, //id
    "name" : "远古巨人",
    "walkSpeed" : 1, //移动速度 多少秒一步
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
                       "defaultImage" : res.GM_Ygjr_png}
};



