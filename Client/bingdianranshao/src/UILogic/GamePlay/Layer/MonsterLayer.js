/**
 * Created by jiachen on 2016/4/2.
 */
var ScheduleTime =0;
var TestTime = 1;
var monsterLayer;
var MonsterLayer = cc.Layer.extend({

    ctor : function(){
        this._super();

        this.schedule(this.updateEvent,ScheduleTime);//计时器
        //this.schedule(this.monsterTest,TestTime);//计时器

        monsterLayer = this;
    },


    addMainCitySprite : function() {

        var leftPoint = {};
        leftPoint.tiled = [];
        leftPoint.tiled.push(cc.p(2, 14));
        leftPoint.point = monsterBackGroundLayer.GetPositionOfTiled(leftPoint.tiled[0]);
        //monsterManager.addMonsterSprite(201,leftPoint,false);

        var rightPoint = {};
        rightPoint.tiled = [];
        rightPoint.tiled.push(cc.p(28,14));
        rightPoint.point = monsterBackGroundLayer.GetPositionOfTiled(rightPoint.tiled[0]);
        //monsterManager.addMonsterSprite(201,rightPoint,true);
        if(GC.IS_HOST){
            monsterManager.addMonsterSprite(201,leftPoint,true);
            monsterManager.addMonsterSprite(201,rightPoint,false);
        }
        else {
            monsterManager.addMonsterSprite(201,rightPoint,true);
            monsterManager.addMonsterSprite(201,leftPoint,false);
        }
    }
    ,
    updateEvent : function(){
        monsterManager.updateMonsterData();
    },

    monsterTest : function(){
        var leftPoint = {};
        leftPoint.tiled = [];
        leftPoint.tiled.push(cc.p(2, 14));
        leftPoint.point = monsterBackGroundLayer.GetPositionOfTiled(leftPoint.tiled[0]);
        monsterManager.addMonsterSprite(2,leftPoint,false);

     },

    //技能效果
    skillAnimate :function(skillConfig,myMonster,elemyMonster){
        //cc.log("skillAnimate");
        if(elemyMonster.m_activity == false){
            return;
        }
        var position;
        if(skillConfig.attribute.isArcAnimate == MonsterAnimateKind.pointAnimate){
            //cc.log("position animate");
            position = elemyMonster.getPosition();
        }
        else {
            position = myMonster.getPosition()
        }
        //cc.log("new a rangedAttackSprite");
        var rangedAttackSprite = new RangedAttackSprite(skillConfig,position,elemyMonster);
        this.addChild(rangedAttackSprite,0);
        if(skillConfig.attribute.isArcAnimate == MonsterAnimateKind.pointAnimate){
            rangedAttackSprite.setAnchorPoint(cc.p(0.5,0.15));
        }
        rangedAttackSprite.startAnimate();
    },
    //技能特效
    rangedAttackEffect : function(config, position){
        var rangedAttackEffect = new RangedAttackEffectSprite(config);
        rangedAttackEffect.setPosition(position);
        rangedAttackEffect.startAnimate();
        this.addChild(rangedAttackEffect);
    },

    addMonsterSprite : function(sprite) {
        this.addChild(sprite);
    }
});