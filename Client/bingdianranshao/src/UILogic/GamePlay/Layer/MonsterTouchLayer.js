/**
 * Created by jiachen on 2016/4/4.
 */

var MonsterTouch ;
var MonsterTouchLayer = cc.Layer.extend({
    m_toolScrollView : null,
    m_nowmoveSprite : null,
    ctor : function(){
        this._super();
        this.addToolScrollView();
        MonsterTouch = this;
    },

    addToolScrollView : function(){
        this.m_toolScrollView = new ccui.ScrollView();
        this.m_toolScrollView.setDirection(ccui.ScrollView.DIR_VERTICAL);
        this.m_toolScrollView.setTouchEnabled(true);
        this.m_toolScrollView.setContentSize(cc.size(GC.w, 150));
        this.m_toolScrollView.x = 150;
        this.m_toolScrollView.y = 0;
        this.addChild(this.m_toolScrollView,150);

        //添加背景
        var bgSprite = cc.Sprite.create(res.GM_TouchlayerTool_png);
        bgSprite.setScaleX(1200.0/bgSprite.getContentSize().width);
        bgSprite.setPosition(30,30);
        this.m_toolScrollView.addChild(bgSprite,0);

        var monsterConfig = MonsterConfig.yuangujuren;
        for(var i = 0; i < 1;i++){
            var monsterTouchSprite = new MonsterTouchSprite(monsterConfig);
            monsterTouchSprite.setPosition((monsterTouchSprite.getContentSize().width/2 + 20) * (i+0.5),monsterTouchSprite.getContentSize().height/2);
            this.m_toolScrollView.addChild(monsterTouchSprite,10);
        }
        var buildingConfig = MonsterConfig.maincity;
        for(var i = 1;i < 2;i++){
            var monsterTouchSprite = new MonsterTouchSprite(buildingConfig);
            monsterTouchSprite.setPosition((monsterTouchSprite.getContentSize().width/2 + 20) * (i+0.5),monsterTouchSprite.getContentSize().height/2);
            this.m_toolScrollView.addChild(monsterTouchSprite,10);
        }
    },

    //tool点击之后的效果
    addListerSprite : function(config,point){
        this.m_nowmoveSprite = cc.Sprite.create(config.defaultImage);
        this.m_nowmoveSprite.setPosition(point);
        this.addChild(this.m_nowmoveSprite);
    },
    moveListerSprite : function(point){
        if(this.m_nowmoveSprite == null){
            return;
        }
        this.m_nowmoveSprite.setPosition(point);
    },
    removeListerSprite :function(){
        this.m_nowmoveSprite.removeFromParent();
        this.m_nowmoveSprite = null;
    }


});