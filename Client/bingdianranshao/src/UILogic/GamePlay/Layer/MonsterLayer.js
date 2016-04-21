/**
 * Created by jiachen on 2016/4/2.
 */
var ScheduleTime =0;
var TestTime = 2;
var monsterLayer;
var MonsterLayer = cc.Layer.extend({

    ctor : function(){
        this._super();

        this.schedule(this.updateEvent,ScheduleTime);//计时器
        //this.schedule(this.monsterTest,TestTime);//计时器

        monsterLayer = this;
    },


    addMainCitySprite : function(){
        var myMainCityPosition;
        var enemyMainCityPosition;
        if(GC.IS_HOST){
            myMainCityPosition = cc.p(200,GC.h_2);
            enemyMainCityPosition = cc.p(GC.w*2 - 200,GC.h_2);
            /*this.addMainCitySprite(config,cc.p(200,GC.h_2),true);
            this.addMainCitySprite(config,cc.p(GC.w*2 - 200,GC.h_2),false);*/
        }
        else{
            myMainCityPosition = cc.p(GC.w*2 - 200,GC.h_2);
            enemyMainCityPosition = cc.p(200,GC.h_2);

        }
    },
    updateEvent : function(){
        monsterManager.updateMonsterData();
    },

    monsterTest : function(){
        var points;
        var config = MonsterConfig.yuangujuren;
        var num = Math.round(Math.random()*3)%3;
        var point = points[num];
        monsterManager.addMonsterSprite(2,point,false);

     },

    //技能效果
    skillAnimate :function(skillConfig,myMonster,elemyMonster){
        cc.log("skillAnimate");
        var rangedAttackSprite = new RangedAttackSprite(skillConfig,myMonster.getPosition(),elemyMonster);
        rangedAttackSprite.startAnimate();
        this.addChild(rangedAttackSprite,0);
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