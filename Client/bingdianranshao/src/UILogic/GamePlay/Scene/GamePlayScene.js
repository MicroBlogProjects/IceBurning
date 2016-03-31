/**
 * Created by jiachen on 2016/3/29.
 */


var GamePlayLayer = cc.Layer.extend({
    monsterLayer : null,
    scrollView : null,
    ctor:function () {
        this._super();
        this.addScrollView();
        this.addMapLayer();
        this.addMonsterLayer();
    },
    addScrollView :function(){
        this.scrollView = new ccui.ScrollView();
        this.scrollView.setDirection(ccui.ScrollView.DIR_HORIZONTAL);
        this.scrollView.setTouchEnabled(true);
        this.scrollView.setContentSize(cc.size(GC.w, GC.h));
        this.scrollView.setInnerContainerSize(cc.size(GC.w*2, GC.h));//可滑动区域
        this.addChild(this.scrollView);
    },

    addMapLayer : function(){
        var tmxMap = cc.TMXTiledMap.create(res.GM_Map_tmx);
        this.scrollView.addChild(tmxMap,LAYER_PRIORITY_MAP);
    },

    addMonsterLayer : function(){
        this.monsterLayer = new MonsterLayer();
        this.scrollView.addChild(this.monsterLayer,LAYER_PRIORITY_MAP);
        var config = MonsterConfig.yuangujuren;
        this.monsterLayer.addMonsterNode(config,1);
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
