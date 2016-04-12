/**
 * Created by jiachen on 2016/4/4.
 */

var MonsterTouch ;
var MonsterTouchLayer = cc.Layer.extend({
    m_toolScrollView : null,
    m_bulidingSelectScrollView : null,
    m_nowmoveSprite : null,
    m_heroSkillSPrite :null,
    //m_monsterSelectScrollView : null,
    //m_buildingSelectScrollView : null,
    ctor : function(){
        this._super();
        //this.addToolScrollView();
        this.addSelectTool();
        this.addHeroSkillIcon();
        MonsterTouch = this;
    },

    /*addToolScrollView : function(){
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
        var buildingConfig = MonsterConfig.xingxingmofata;
        for(var i = 1;i < 2;i++){
            var monsterTouchSprite = new MonsterTouchSprite(buildingConfig);
            monsterTouchSprite.setPosition((monsterTouchSprite.getContentSize().width/2 + 20) * (i+0.5),monsterTouchSprite.getContentSize().height/2);
            this.m_toolScrollView.addChild(monsterTouchSprite,10);
        }
    },*/

    addSelectTool : function(){

        this.m_toolScrollView = new ccui.ScrollView();
        this.m_toolScrollView.setDirection(ccui.ScrollView.DIR_VERTICAL);
        this.m_toolScrollView.setTouchEnabled(true);
        this.m_toolScrollView.setContentSize(cc.size(250, 50));
        this.m_toolScrollView.x = 150;
        this.m_toolScrollView.y = 30;
        this.addChild(this.m_toolScrollView,151);

        this.m_bulidingSelectScrollView = new ccui.ScrollView();
        this.m_bulidingSelectScrollView.setDirection(ccui.ScrollView.DIR_VERTICAL);
        this.m_bulidingSelectScrollView.setTouchEnabled(true);
        this.m_bulidingSelectScrollView.setContentSize(cc.size(250,50));
        this.m_bulidingSelectScrollView.setPosition(cc.p(530,23));
        this.addChild(this.m_bulidingSelectScrollView,151);

        this.selectTool = ccs.load(res.GM_SelectTool_json).node;
        //this.m_monsterSelectScrollView = ccui.helper.seekWidgetByName(this.selectTool,"ScrollView_1");
        //this.m_buildingSelectScrollView = ccui.helper.seekWidgetByName(this.selectTool,"ScrollView_2");
        //this.selectTool.setPosition(cc.p(0,GC.w - 90));
        this.addChild(this.selectTool,150);
        this.addIcon();
    },
    addIcon : function(){
        config = MonsterConfig.yuangujuren;
        for(var i = 0; i < 5;i++){
            var sprite = new MonsterTouchSprite(config);
            sprite.setPosition((sprite.getContentSize().width+10)*(i+0.5),sprite.getContentSize().height/2);
            this.m_toolScrollView.addChild(sprite);
        }
        config = MonsterConfig.xingxingmofata;
        for(var i = 0; i < 4;i++){
            var sprite = new MonsterTouchSprite(config);
            sprite.setPosition((sprite.getContentSize().width+10)*(i+0.5),sprite.getContentSize().height/2);
            //this.m_bulidingSelectScrollView.setInnerContainerSize(cc.size(1000,30));
            this.m_bulidingSelectScrollView.addChild(sprite);
        }

    },
    addHeroSkillIcon : function(){
        var button = ccui.Button.create(res.HS_HongqiuIcon_png);
        button.setPosition(cc.p(GC.w_2-10,50));
        button.addClickEventListener(this.heroButtonClick);
        this.addChild(button)
    },

    heroButtonClick : function(){
        //monsterBackGroundLayer.heroSkillAniamte();
    },

    //tool点击之后的效果
    addListerSprite : function(config,point){
        this.m_nowmoveSprite = cc.Sprite.create(config.attribute.defaultImage);
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