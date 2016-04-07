/**
 * Created by jiachen on 2016/4/4.
 */

var MonsterTouch ;
var MonsterTouchLayer = cc.Layer.extend({
    m_toolScrollView : null,
    m_nowmoveSprite : null,
    m_clipperNode : null,
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

        config = MonsterConfig.yuangujuren;
        for(var i = 0; i < 10;i++){
            var monsterTouchSprite = new MonsterTouchSprite(config);
            monsterTouchSprite.setPosition((monsterTouchSprite.getContentSize().width/2 + 20) * (i+0.5),monsterTouchSprite.getContentSize().height/2);
            this.m_toolScrollView.addChild(monsterTouchSprite,10);
        }
    },

    //tool点击之后的效果
    addListerSprite : function(point){
        this.m_nowmoveSprite = MonsterConfig.yuangujuren;
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
    },

    addClipperNode :function(){
        var baLayer = cc.LayerColor.create(cc.color(0,0,0,150));

        //画个正方形
        /*var rectangular = new cc.DrawNode();
        var origin = cc.p(0,0);
        var destination = cc.p(25*32,64);
        var color = cc.color(0,0,0);
        rectangular.setPosition(5*32,16*32);
        rectangular.drawRect(origin,destination,color);*/


        //设置模板
        var stencil = cc.Node.create();
        stencil.addChild(rectangular);
        //设置
        this.m_clipperNode = cc.ClippingNode.create(stencil);
        this.m_clipperNode.setInverted(true);
        this.m_clipperNode.setAlphaThreshold(1.0);
        this.m_clipperNode.addChild(baLayer);
        this.addChild(this.m_clipperNode);
    },

    getRectangular : function(posiition, destination){
        var rectangular = new cc.DrawNode();
        var origin = cc.p(0,0);
        var color = cc.color(0,0,0);
        rectangular.setPosition(posiition);
        rectangular.drawRect(origin,destination,color);
        return rectangular;
    },

    removeClipperNode : function(){
        this.m_clipperNode.removeFromParent();
        this.m_clipperNode = null;
    }

});