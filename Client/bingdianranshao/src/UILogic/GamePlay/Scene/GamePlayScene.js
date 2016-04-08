/**
 * Created by jiachen on 2016/3/29.
 */


var gamePlayLayer;
var GamePlayLayer = cc.Layer.extend({
    monsterBackgroundLayer : null,
    scrollView : null,
    monsterTouchlayer: null,
    TMXTiledMap :null,
    ctor:function () {
        this._super();
        this.addScrollView();
        this.addMonsteBackgroundrLayer();
        this.addMonsterTouchlayer();
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
    test : function(){
        var config = MonsterConfig.yuangujuren;
        this.monsterBackgroundLayer.test(config, cc.p(200,200));
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
