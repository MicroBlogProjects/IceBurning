/**
 * Created by jiachen on 2016/3/29.
 */


var GamePlayLayer = cc.Layer.extend({
    monsterBackgroundLayer : null,
    scrollView : null,
    monsterTouchlayer: null,
    ctor:function () {
        this._super();
        this.addScrollView();
        this.addMonsteBackgroundrLayer();
        this.addMonsterTouchlayer();
    },
    addScrollView :function(){
        this.scrollView = new ccui.ScrollView();
        this.scrollView.setDirection(ccui.ScrollView.DIR_HORIZONTAL);
        this.scrollView.setTouchEnabled(true);
        this.scrollView.setContentSize(cc.size(GC.w, GC.h));
        this.scrollView.setInnerContainerSize(cc.size(GC.w*2, GC.h));//可滑动区域
        this.addChild(this.scrollView);
    },

    addMonsteBackgroundrLayer : function(){
        this.monsterBackgroundLayer = new MonsterBackgroundLayer();
        var tmxMap = cc.TMXTiledMap.create(res.GM_Map_tmx);
        this.scrollView.addChild(tmxMap,LAYER_PRIORITY_MAP);
        this.scrollView.addChild(this.monsterBackgroundLayer,LAYER_PRIORITY_MAP);
        this.test();
    },

    addMonsterTouchlayer :function(){
      this.monsterTouchlayer = new MonsterTouchLayer();
        this.addChild(this.monsterTouchlayer);
    },
    test : function(){
        var config = MonsterConfig.yuangujuren;
        this.monsterBackgroundLayer.test(config, new cc.Point(200,200));
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
