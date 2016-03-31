/**
 * Created by jiachen on 2016/3/29.
 */


var GamePlayLayer = cc.Layer.extend({
    monsterLayer : null,
    onEnter:function () {
        this._super();
        //this.addMapLayer();
        //this.addMonsterLayer();
    },

    addMapLayer : function(){
        var tmxMap = cc.TMXTiledMap.create(res.GM_Map_tmx);
        this.addChild(tmxMap,LAYER_PRIORITY_MAP);
    },

    addMonsterLayer : function(){
        this.monsterLayer = new MonsterLayer();
        this.addChild(this.monsterLayer,LAYER_PRIORITY_MAP);
        var config = MonsterConfig.yuangujuren;
        this.monsterLayer.addMonsterNode(config,1);
    }
});
var GamePlayScene = cc.Scene.extend({
    gamePlayLayer :null,
    scrollView : null,
    //eventListenTouch : null,
    ctor :function(){
        this._super();
        //gamePlaylayer = new GamePlayLayer();
        //this.addChild(gamePlaylayer);
        this.addScrollView();
    },
    addScrollView : function(){
        this.scrollView = ccui.ScrollView.create();
        this.addChild(this.scrollView);
        this.scrollView.setDirection(ccui.SCROLLVIEW_DIRECTION_BOTH);
        this.scrollView.setTouchEnabled(true);
        this.scrollView.setContentSize(GC.w, GC.h);
        var tmxMap = cc.TMXTiledMap.create(res.GM_Map_tmx);
        var mapLayer = cc.Layer.create();
        mapLayer.addChild(tmxMap);
        mapLayer.setContentSize(GC.w*2,GC.h);
        var s = mapLayer.getContentSize();
        this.scrollView.addChild(mapLayer);
    }
    /*addEventListenTouch : function()
    {
        this.eventListen = cc.EventListener.create({
            event: cc.EventListener.TOUCH_ONE_BY_ONE, //单点触摸
            swallowTouches: true,   // 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞掉事件，不再向下传递。
        });
        ;
    }*/
});
