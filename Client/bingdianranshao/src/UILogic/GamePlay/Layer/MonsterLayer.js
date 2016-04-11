/**
 * Created by jiachen on 2016/4/2.
 */

    //弃用
var MonsterLayer = cc.Layer.extend({

    m_tagerSprite : null,
    m_boold : null,
    m_isMyMonster : true,
    //属性
    m_id : null,
    m_name : null,
    m_walkSpeed : null,
    m_HP : null,
    m_sightRadius : null,
    m_defense : null,
    m_attack : null,
    m_attackRadius : null,
    m_attackSpeed : null,
    m_direct : null,
    //动画相关
    m_prefixName :null,
    m_walkingAnimateAccount : null,
    m_walkingAnimatePlist : null,
    m_attackAnimateAccount : null,
    m_attackAnimatePlist : null,
    m_deathAnimatePlist : null,
    m_deathAnimateAccount:null,
    m_nowAnimateAction : null,
    ctor :function(config){
        this._super();
        this.m_tagerSprite = cc.Sprite.create(config.defaultImage);
        this.addChild(this.m_tagerSprite);
        //var contentSize = this.m_tagerSprite.getContentSize();
        //this.setContentSize(contentSize);
        this.addBlood();


        var attributeConfig = config.attribute;
        var animateConfig  = config.animate;
        //设置属性
        this.m_id = attributeConfig.id;
        this.m_name = attributeConfig.name;
        this.m_walkSpeed = attributeConfig.walkSpeed;
        this.m_HP = attributeConfig.HP;
        this.m_sightRadius = attributeConfig.sightRadius;
        this.m_defense = attributeConfig.defense;
        this.m_attack = attributeConfig.attack;
        this.m_attackSpeed = attributeConfig.attackSpeed;
        this.m_attackRadius = attributeConfig.attackRadius;
        this.director = 1; // 默认正方向 1位正

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
    addBlood :function(){
        var tagerSize = this.m_tagerSprite.getContentSize();
        //背景
        var backgroundSprite = cc.Sprite.create(res.GM_BackgroundBolld_png);
        backgroundSprite.setPosition(0,tagerSize.height/2);
        backgroundSprite.setScaleX(tagerSize.width/backgroundSprite.getContentSize().width*0.8);
        backgroundSprite.setScaleY(10/backgroundSprite.getContentSize().height);
        this.addChild(backgroundSprite,10);
        //进度条
        var booldSprite ;
        if(this.m_isMyMonster){
            booldSprite = cc.Sprite.create(res.GM_RedBlood_png);
        }
        else{
            booldSprite = cc.Sprite.create(res.GM_BlueBlood_png)
        }
        booldSprite.setScaleX(tagerSize.width/booldSprite.getContentSize().width*0.8);
        booldSprite.setScaleY(10/booldSprite.getContentSize().height);
        booldSprite.setPosition(0,tagerSize.height/2);
        booldSprite.setContentSize(85,10);
        this.m_boold = cc.ProgressTimer.create(booldSprite);
        var booldSize = this.m_boold.getContentSize();
        this.m_boold.setPosition(0,tagerSize.height/2);
        if(this.m_isMyMonster){
            //this.m_boold.setReverseDirection(true);
        }
        var size = this.m_boold.getContentSize();
        this.m_boold.type = cc.ProgressTimer.TYPE_BAR;
        this.m_boold.setMidpoint(cc.p(0.0,0.5));
        this.m_boold.setBarChangeRate(cc.p(1.0,0.0));
        this.m_boold.setPercentage(80);
        backgroundSprite.addChild(this.m_boold);
        //this.addChild(this.m_boold);
    }
});