/**
 * Created by jiachen on 2016/4/10.
 */

var HeroSkillSprite = cc.Sprite.extend({
    m_config : null,
    m_nowAnimateAction : null,
    ctor : function(config){
        this.m_config = config;
        this._super(config.defaultImage)
    },
    startAnimate : function(){
        this.stopAnimate();

        var plistFile = config.animatePlist;
        var prefixName = config.prefix;
        var totalTime = config.time;
        var account = config.account;

        cc.spriteFrameCache.addSpriteFrames(plistFile);
        var animFrames = [];
        for(var i = 0; i < account;i++) {
            var str = prefixName + i + ".png";
            var frame = cc.spriteFrameCache.getSpriteFrame(str);
            animFrames.push(frame);
        }

        var speed = totalTime * 1.0 / account;
        var animation = new cc.Animation(animFrames, speed);
        this.m_nowAnimateAction = new cc.Animate(animation);
        var position = this.getPosition();
        var point;
        if(GC.IS_HOST){
            point = cc.p(position.x + 1500,position.y);
        }
        else {
            point = cc.p(position.x -1500,position.y);
        }
        var easeMove = cc.moveTo(totalTime, point)/*.easing(cc.easeSineOut())*/;
        this.runAction(cc.sequence(this.m_nowAnimateAction,easeMove,cc.callFunc(this.attackEndCallFunc,this)));
    },
    attackEndCallFunc : function(){
        this.removeFromParent();
    },
    stopAnimate : function(){
        this.stopAllActions();
    }
});