/**
 * Created by JiaChen on 2016/4/17.
 */


var RangedAttackEffectSprite = cc.Sprite.extend({

    m_animateConfig : null,
    ctor : function(config){
        this.m_animateConfig = config;
        this._super(config.defaultImage);
    },

    startAnimate : function(){
        var config = this.m_animateConfig;
        this.stopAllActions();

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
        this.runAction(cc.sequence(this.m_nowAnimateAction,cc.callFunc(this.attackCallFunc,this)));
    },
    attackCallFunc : function(sender){
        sender.removeFromParent();
    }
});
