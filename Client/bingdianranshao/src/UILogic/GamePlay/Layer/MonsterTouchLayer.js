/**
 * Created by jiachen on 2016/4/4.
 */

var MonsterTouch ;
var MonsterTouchLayer = cc.Layer.extend({
    monsterPanel : null,
    buildingPanel : null,
    m_nowmoveSprite : null,
    monsters : null,
    ctor : function(){
        this._super();
        this.monsters = [];
        this.addSelectTool();
        //this.addHeroSkillIcon();
        MonsterTouch = this;
    },


    addSelectTool : function(){


        this.selectTool = ccs.load(res.GM_SelectTool_json).node;
        this.monsterPanel = ccui.helper.seekWidgetByName(this.selectTool,"Monster_Panel");
        this.buildingPanel = ccui.helper.seekWidgetByName(this.selectTool,"BuildingPanel")
        this.addChild(this.selectTool,150);
        this.addIcon();
    },
    addIcon : function(){

        for(var i = 0; i < MonsterIDList.length; i++){
            var ID = MonsterIDList[i];
            var config = MonsterConfig[""+ID];
            var sprite = new MonsterTouchSprite(config);
            this.monsters.push(sprite);
            sprite.setContentSize(sprite.getContentSize().width*2,sprite.getContentSize().height*2);
            sprite.setPosition(40+(6+sprite.getContentSize().width)*(i+0.5),sprite.getContentSize().height/2+50);
            this.monsterPanel.addChild(sprite);
        }

        for(var i = 0; i < BuildingIDlist.length;i++){
            var ID = BuildingIDlist[i];
            var config = MonsterConfig[""+ID];
            var sprite = new MonsterTouchSprite(config);
            sprite.setContentSize(sprite.getContentSize().width*2,sprite.getContentSize().height*2);
            sprite.setPosition(40+(60+sprite.getContentSize().width)*(i+0.5),sprite.getContentSize().height/2+51);
            this.monsters.push(sprite);
            this.buildingPanel.addChild(sprite);
        }
    },

    changedCoin : function(coin){
        for(var i = 0 ;i < this.monsters.length;i++){
            var sprite = this.monsters[i];
            sprite.changeProgressTimer(coin);
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