/**
 * Created by jiachen on 2016/3/29.
 */


var gamePlayLayer;
var GamePlayLayer = cc.Layer.extend({

    scrollView : null,
    backgroundLayer : null,
    monstarLayer : null,
    monsterTouchlayer: null,
    
    playerInfomation : null,
    selectTool : null,
    timeTitle : null,
    GC_Time : 0,

    ctor:function () {
        this._super();
        this.addBackgroundpScrollView();
        this.addMonsterLayerLayer();
        this.addMonsterTouchlayer();
        this.playerInfomation = ccs.load(res.GM_PlayerInfomation_json).node;
        this.TimeTitle = ccui.helper.seekWidgetByName(this.playerInfomation,"m_time_label");

        this.addChild(this.playerInfomation,150);
        this.schedule(this.updataTime,1);//计时器
        gamePlayLayer = this;
    },
    addBackgroundpScrollView :function(){

        this.scrollView = new ccui.ScrollView();
        this.scrollView.setDirection(ccui.ScrollView.DIR_HORIZONTAL);
        this.scrollView.setTouchEnabled(true);
        this.scrollView.setContentSize(cc.size(GC.w, GC.h));
        this.scrollView.setInnerContainerSize(cc.size(GC.w*2, GC.h));//可滑动区域
        this.addChild(this.scrollView);
        if(GC.IS_HOST == false){
            this.runAction(cc.sequence(cc.delayTime(0.05), cc.callFunc(function(){this.scrollView.jumpToRight()}.bind(this))));
        }
        this.backgroundLayer = new MonsterBackgroundLayer();
        this.scrollView.addChild(this.backgroundLayer,LAYER_PRIORITY_MAP);
    },
    addMonsterLayerLayer : function () {
        this.monstarLayer = new MonsterLayer();
        this.monstarLayer.addMainCitySprite();
        this.scrollView.addChild(this.monstarLayer,LAYER_PRIORITY_MONSTER);

    },

    updataTime : function(){
        var secondTitle;
        var minutesTitle;
        this.GC_Time++;
        var seconds = this.GC_Time%60;
        var minutes = (this.GC_Time / 60)%60;
        minutes = parseInt(minutes);
        if(seconds < 10){
            secondTitle = "0" + seconds;
        }
        else {
            secondTitle = "" + seconds;
        }
        if(minutes < 10){
            minutesTitle = "0"+minutes+":";
        }
        else {
            minutesTitle = ""+minutes+";";
        }
        var timeTitle = "00:"+minutesTitle+secondTitle;
        this.TimeTitle.setString(timeTitle);

    },

    addMonsterTouchlayer :function(){
        this.monsterTouchlayer = new MonsterTouchLayer();
        this.addChild(this.monsterTouchlayer,LAYER_PRIORITY_TOUCH);
    },

    addSelectTool : function(){
        this.selectTool = ccs.load(res.GM_SelectTool_json).node;
        //this.selectTool.setPosition(cc.p(0,GC.w - 90));
        this.addChild(this.selectTool,150);
    }


});
var GamePlayScene = cc.Scene.extend({
    gamePlayLayer :null,
    monsterManager:null,
    checkPathManger:null,
    algorithmOfStatus:null,
    onEnter :function(){
        this._super();
        this.monsterManager = new MonsterManager();
        this.checkPathManger = new CheckPathManager();
        this.algorithmOfStatus = new AlgorithmOfStatus();
        this.addGamePlay();
    },
    addGamePlay : function(){
        this.gamePlayLayer = new GamePlayLayer();
        this.addChild(this.gamePlayLayer);
    }
});
