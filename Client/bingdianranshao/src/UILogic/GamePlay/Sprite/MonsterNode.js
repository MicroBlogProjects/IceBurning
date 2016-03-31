/**
 * Created by jiachen on 2016/3/29.
 */

MonsterNode =  cc.Node.extend({
    //属相
    m_target : null,
    m_name : null,
    m_speed : null,
    m_direct  :null,
    m_HP : null,
    m_attack : null,

    //动画相关
    m_prefixName :null,
    m_walkingAnimateAccount : null,
    m_walkingAnimatePlist : null,
    m_attackAnimateAccount : null,
    m_attackAnimatePlist : null,
    m_deathAnimatePlist : null,
    m_deathAnimateAccount:null,

    m_nowAnimateAction : null,



    walkingAnimationAction :null,

    ctor : function(config,direct){
        this._super();
        var attributeConfig = config.attribute;
        var animateConfig  = config.animate;

        //创建sprite
        this.m_target = cc.Sprite.create(animateConfig.defaultImage);
        var contentSize = this.m_target.getContentSize();
        this.setContentSize(contentSize);

        //设置属性
        this.m_name = attributeConfig.name;
        this.m_speed = attributeConfig.speed;
        this.m_direct = direct; //1为正方向,-1为反方向
        this.m_HP = attributeConfig.HP;
        this.m_attack = attributeConfig.attack;

        //设置动画
        this.m_prefixName = animateConfig.prefixName;
        //行走动画
        this.m_walkingAnimateAccount = animateConfig.walkingAnimateAccount;
        this.m_walkingAnimatePlist = animateConfig.walkingAnimatePlist;
        //攻击动画
        this.m_attackAnimateAccount = animateConfig.attackAnimateAccount;
        this.m_attackAnimatePlist = animateConfig.attackAnimatePlist;
        //死亡动画
        this.m_deathAnimateAccount = animateConfig.deathAnimateAccount;
        this.m_deathAnimatePlist = animateConfig.deathAnimatePlist;
    },

    startAnimate : function(plistFile, account, imageName){
        cc.spriteFrameCache.addSpriteFrames(plistFile);
        var animFrames = [];
        for(var i = 0; i < account;i++) {
            var str = imageName + i + ".png";
            var frame = cc.spriteFrameCache.getSpriteFrame(str);
            animFrames.push(frame);
        }
        var animation = new cc.Animation(animFrames, 0.1);
        this.m_nowAnimateAction = new cc.Animate(animation);
        this.m_nowAnimateAction.retain();
        this.m_target.runAction(cc.repeatForever(this.m_nowAnimateAction));
    },

    stopAnimate : function(){

    },

    walkingAnimate :function(){
        this.startAnimate(this.m_walkingAnimatePlist, this.m_walkingAnimateAccount,this.m_prefixName + "walking");
    },

    attackAnimate : function(){
        this.startAnimate(this.m_attackAnimatePlist, this.m_attackAnimateAccount,this.m_prefixName + "attack");
    },
    deathAnimate : function()
    {
        this.startAnimate(this.m_deathAnimatePlist, this.m_deathAnimateAccount,this.m_prefixName + "death");
    }
});