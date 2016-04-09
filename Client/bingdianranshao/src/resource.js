var res = {
    //HelloWorld_png : "res/HelloWorld.png",
    CloseNormal_png : "res/CloseNormal.png",
    CloseSelected_png : "res/CloseSelected.png",

    //share

    //MainMenu
    MM_MainScene_json : "res/MainMenu/MainScene.json",
    MM_BgMusic_mp3 : "res/Sound/Music/MainMusic.mp3",
    MM_Mune_png :     "res/MainMenu/menu.png",
    MM_ButtonEffect : "res/Sound/Effect/buttonEffect.mp3",
    MM_Flare_jpg :     "res/MainMenu/flare.jpg",

    //GamePlay
    GM_Map_tmx : "res/GamePlay/Map/c.tmx",
    GM_Map_png : "res/GamePlay/Map/c.png",

    //monster
    GM_MainCity_png :     "res/GamePlay/Monster/xingxingmofata/xingxingmofata.png",
    GM_RedBlood_png     : "res/GamePlay/Monster/bloodImage/RedBlood.png",
    GM_BlueBlood_png :    "res/GamePlay/Monster/bloodImage/BlueBlood.png",
    GM_BackgroundBolld_png : "res/GamePlay/monster/bloodImage/BackgroundBlood.png",

    //monstertouchlayr
    GM_TouchlayerTool_png : "res/GamePlay/MonsterTouchLayer/tool.png",
    GM_PickImage_png : "res/GamePlay/MonsterTouchLayer/pickImage.png",

    //setting
    ST_Title_png : "res/Setting/menuTitle.png",


    //远古巨人
    GM_Ygjrwalking_plist :  "res/GamePlay/Monster/yuangujuren/ygjrwalking.plist",
    GM_Ygjrwalking_png :     "res/GamePlay/Monster/yuangujuren/ygjrwalking.png",
    GM_Ygjr_png :             "res/GamePlay/Monster/yuangujuren/ygjr.png",
    GM_Ygjrattack_plist :    "res/GamePlay/Monster/yuangujuren/ygjrattack.plist",
    GM_Ygjrattack_png :      "res/GamePlay/Monster/yuangujuren/ygjrattack.png",
    GM_Ygjrdeath_plist :     "res/GamePlay/Monster/yuangujuren/ygjrdeath.plist",
    GM_Ygjrdeath_png :        "res/GamePlay/Monster/yuangujuren/ygjrdeath.png",

    //星星魔法塔
    GM_Xxmft_Png      :    "res/GamePlay/Monster/xingxingmofata/xingxingmofata.png",
    GM_XxmftSkill_Png :   "res/GamePlay/Monster/xingxingmofata/xxmftskill.png",
    GM_XxmftAttack_Plist :  "res/GamePlay/Monster/xingxingmofata/xxmftattack.plist",
    GM_XxmftAttack_Png :  "res/GamePlay/Monster/xingxingmofata/xxmftattack.png",
    GM_XxmftAttackDeath_Plist : "res/GamePlay/Monster/xingxingmofata/xxmftattackdeath.plist",
    GM_XxmftAttackDeath_png : "res/GamePlay/Monster/xingxingmofata/xxmftattackdeath.png",
    GM_XxmftDeath_Plist : "res/GamePlay/Monster/xingxingmofata/xxmftdeath.plist",
    GM_XxmftDeath_Png : "res/GamePlay/Monster/xingxingmofata/xxmftdeath.png",
    GM_XxmftSkillAttack_Plist : "res/GamePlay/Monster/xingxingmofata/xxmftSkillAttack.plist",
    GM_XxmftSkillAttack_Png : "res/GamePlay/Monster/xingxingmofata/xxmftSkillAttack.png",
    GM_XxmftSkillDeath_Plist : "res/GamePlay/Monster/xingxingmofata/xxmftSkillDeath.plist",
    GM_XxmftSkillDeath_Png : "res/GamePlay/Monster/xingxingmofata/xxmftSkillDeath.png"





};

var g_resources = [];
for (var i in res) {
    g_resources.push(res[i]);
}
