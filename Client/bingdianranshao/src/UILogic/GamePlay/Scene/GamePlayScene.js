/**
 * Created by jiachen on 2016/3/29.
 */


var gamePlayLayer;
var GamePlayLayer = cc.Layer.extend({
    monsterBackgroundLayer : null,
    scrollView : null,
    monsterTouchlayer: null,
    TMXTiledMap :null,
    playerInfomation : null,
    selectTool : null,
    timeTitle : null,
    GC_Time : 0,
    ctor:function () {
        this._super();
        this.addScrollView();
        this.addMonsteBackgroundrLayer();
        this.addMonsterTouchlayer();
        this.playerInfomation = ccs.load(res.GM_PlayerInfomation_json).node;
        this.TimeTitle = ccui.helper.seekWidgetByName(this.playerInfomation,"m_time_label");
        //this.addSelectTool();

        this.addChild(this.playerInfomation,150);
        this.schedule(this.updataTime,1);//计时器
        gamePlayLayer = this;
    },
    addScrollView :function(){
        this.scrollView = new ccui.ScrollView();
        this.scrollView.setDirection(ccui.ScrollView.DIR_HORIZONTAL);
        this.scrollView.setTouchEnabled(true);
        this.scrollView.setContentSize(cc.size(GC.w, GC.h));
        this.scrollView.setInnerContainerSize(cc.size(GC.w*2, GC.h));//可滑动区域
        this.addChild(this.scrollView);
        if(GC.IS_HOST == false){
            this.runAction(cc.sequence(cc.delayTime(0.05), cc.callFunc(function(){this.scrollView.jumpToRight()}.bind(this))));
        }
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
    addMonsteBackgroundrLayer : function(){
        this.TMXTiledMap = cc.TMXTiledMap.create(res.GM_Map_tmx);
        /*var sprite = cc.Sprite.create(res.GM_PickImage_png);
        var mapLayer = this.TMXTiledMap.getLayer("MapLayer");
        var sp = mapLayer.getTileAt(cc.p(10,10));
        sp.addChild(sprite);*/
        this.scrollView.addChild(this.TMXTiledMap,LAYER_PRIORITY_MAP);
        this.monsterBackgroundLayer = new MonsterBackgroundLayer();
        this.scrollView.addChild(this.monsterBackgroundLayer,LAYER_PRIORITY_MAP);
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
    scrollView : null,
    onEnter :function(){
        this._super();
        this.addGamePlay();
    },
    addGamePlay : function(){
        this.gamePlayLayer = new GamePlayLayer();
        this.addChild(this.gamePlayLayer);
    }
});
