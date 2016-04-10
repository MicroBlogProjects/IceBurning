/**
 * Created by jiachen on 2016/4/8.
 */

var SkillSprite = cc.Sprite.extend({
    m_attack : null,
    m_attackRadius :null,
    m_walkSpeed : null,
    m_attackConfig : null,
    m_nowAnimateAction : null,


    ctor:function(config){
        var attributeConfig = config.attribute;
        this._super(attributeConfig.defaultImage);
        this.m_attack = attributeConfig.attack;
        this.m_walkSpeed = attributeConfig.walkingSpeed;
        this.m_attackRadius = attributeConfig.attackRadius;

        this.m_attackConfig = config.attack;
    },

    startAnimate : function(config){
        this.stopAnimate();

        var plistFile = config.animatePlist;
        var prefixname = config.prefix;
        var totalTime = config.time;
        var account = config.account;

        cc.spriteFrameCache.addSpriteFrames(plistFile);
        var animFrames = [];
        for(var i = 0; i < account;i++) {
            var str = prefixname + i + ".png";
            var frame = cc.spriteFrameCache.getSpriteFrame(str);
            animFrames.push(frame);
        }

        var speed = totalTime * 1.0 / account;
        var animation = new cc.Animation(animFrames, speed);
        this.m_nowAnimateAction = new cc.Animate(animation);
    },

    attackAnimate : function(enemyMonster){
        var config = this.m_attackConfig.begin;

        this.startAnimate(config);
        var endConfig = this.m_attackConfig.end;
        var argu = {
            "enemyMonster" : enemyMonster,
            "myMonster" : this,
            "endAnimate" : endConfig
        };
        this.setPosition(enemyMonster.getPosition());
        this.runAction(cc.sequence(this.m_nowAnimateAction,cc.callFunc(this.attackCallFunc,this,argu)));
    },

    stopAnimate : function(){
        this.stopAllActions();
    },

    attackCallFunc : function(sprite,argu){
        var enemyMonster = argu.enemyMonster;
        var myMonster = argu.myMonster;
        var endAnimate = argu.endAnimate;
        enemyMonster.m_HP -= myMonster.m_attack * 1.0 / enemyMonster.m_defense +1;
        if(endAnimate == null || endAnimate == undefined){
            this.m_state = null;
        }
        else {
            this.startAnimate(endAnimate);
            this.runAction(cc.sequence(this.m_nowAnimateAction,cc.callFunc(this.attackEndCallFunc,this)));
        }

    },
    attackEndCallFunc : function(){
        this.removeFromParent();
    }
});
