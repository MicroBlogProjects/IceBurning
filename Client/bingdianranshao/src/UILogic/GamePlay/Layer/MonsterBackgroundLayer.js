/**
 * Created by jiachen on 2016/3/29.
 */
//弃用
//管理所有的怪物
var ScheduleTime =1.0/10;
var TestTime = 2;
var monsterBackGroundLayer;

var MonsterBackgroundLayer = cc.Layer.extend({
    m_clipperNode : null,
    buildingTickLayer : null,

    TMXTiledMap :null,

    ctor : function(){
        this._super();
        this.TMXTiledMap = cc.TMXTiledMap.create(res.GM_Map_tmx);
        this.addChild(this.TMXTiledMap,0);
        monsterBackGroundLayer = this;

    },

    //拖动怪物的效果
    addClipperNode :function(){
        //设置模板
        /*var stencil = checkPathManager.getStencil();
        //设置
        this.m_clipperNode = cc.ClippingNode.create(stencil);
        this.m_clipperNode.setInverted(true);//底板可见
        this.m_clipperNode.setAlphaThreshold(1.0);
        //设置灰色的底板
        var baLayer = cc.LayerColor.create(cc.color(0,0,0,150));
        baLayer.setScaleX(4);
        this.m_clipperNode.addChild(baLayer);
        this.addChild(this.m_clipperNode,0);*/
    },
    removeClipperNode : function(){
        /*this.m_clipperNode.removeFromParent();
        this.m_clipperNode = null;*/
    },

    //技能效果
    skillAnimate :function(skillConfig,elemy){
        var skillSprite = new SkillSprite(skillConfig);
        skillSprite.setPosition(elemy.getPosition().x,elemy.getPosition().y -60 );
        skillSprite.attackAnimate(elemy);
        this.addChild(skillSprite);
    },

    //拖动建筑物效果
    addBuildingTick : function(){
        /*this.buildingTickLayer = new BuildingTicklayer();
        this.addChild(this.buildingTickLayer,LAYER_PRIORITY_TOUCH-1);
        var positions = checkPathManager.getBuildintPositions();
        for(var i = 0; i < positions.length; i++){
            var position = positions[i];
            this.buildingTickLayer.addTickSprite(position);
        }*/
    },
    removeBuildingTick : function(){
        //this.buildingTickLayer.removeFromParent();
        //this.buildingTickLayer = null;
    }


});
