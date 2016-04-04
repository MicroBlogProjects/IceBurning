/**
 * Created by jiachen on 2016/4/1.
 */

MonsterSprite = cc.Sprite.extend({
    m_isMyMonster : true,
    m_state :null,
    m_activity :true,
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

    //血条
    m_booldProgressTimer :null,
    m_total_HP :null,

    ctor : function(config,isMyMonster){
        this._super(config.defaultImage);
        var attributeConfig = config.attribute;
        var animateConfig  = config.animate;
        this.m_isMyMonster = isMyMonster;
        this.m_activity = true;

        //设置属性
        this.m_id = attributeConfig.id;
        this.m_name = attributeConfig.name;
        this.m_walkSpeed = attributeConfig.walkSpeed;
        this.m_HP = attributeConfig.HP;
        this.m_total_HP = this.m_HP;
        this.m_sightRadius = attributeConfig.sightRadius;
         this.m_defense = attributeConfig.defense;
        this.m_attack = attributeConfig.attack;
        this.m_attackSpeed = attributeConfig.attackSpeed;
        this.m_attackRadius = attributeConfig.attackRadius;
        this.director = 1; // 默认正方向 1位正
        this.scheduleUpdate();

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

        this.addBooldProgressTimer();
    },

    startAnimate : function(plistFile, account, imageName, totalTime, isflip, callFunc, enemyMonster){
        this.stopAnimate();
        cc.spriteFrameCache.addSpriteFrames(plistFile);
        var animFrames = [];
        for(var i = 0; i < account;i++) {
            var str = imageName + i + ".png";
            var frame = cc.spriteFrameCache.getSpriteFrame(str);
            animFrames.push(frame);
        }
        if(isflip){
            this.setFlippedX(true);
        }
        speed = totalTime * 1.0 / account;
        var animation = new cc.Animation(animFrames, speed);
        this.m_nowAnimateAction = new cc.Animate(animation);
        /*if(this.m_state == MonsterState.Death){ //执行一次
            this.runAction(cc.sequence(this.m_nowAnimateAction,cc.callFunc(this.deathCallFunc,this)));
        }
        else{
            this.runAction(cc.sequence(cc.repeatForever(this.m_nowAnimateAction),cc.callFunc(this.deathCallFunc,enemyMonster)));
            //this.runAction(cc.repeatForever(this.m_nowAnimateAction));
        }*/
        //this.runAction(cc.repeat(this.m_nowAnimateAction,1))
    },

    deathCallFunc : function(){
        this.m_activity = false;
        this.removeFromParent();
        this.m_state = null;
        //this.runAction(cc.sequence(this.m_nowAnimateAction,cc.callFunc(this.walkingCallFunc,this)));
    },
    attackCallFunc : function(sprite,argu){
        enemyMonster = argu.enemyMonster;
        myMonster = argu.myMonster;
        enemyMonster.m_HP -= myMonster.m_attack * 1.0 / enemyMonster.m_defense +1;//至少一点伤害
        this.m_state = null;
        //this.runAction(cc.sequence(this.m_nowAnimateAction,cc.callFunc(this.attackCallFunc,this,argu)));

    },
    walkingCallFunc : function(){
        this.m_state = null;
        //this.runAction(cc.sequence(this.m_nowAnimateAction,cc.callFunc(this.walkingCallFunc,this)));
    },
    stopAnimate : function(){
        this.stopAllActions();
    },

    walkingAnimate :function(enemyMonster){
        if (this.m_state == MonsterState.WalkingRight){
            return;
        }
        this.m_state = MonsterState.WalkingRight
        this.startAnimate(this.m_walkingAnimatePlist, this.m_walkingAnimateAccount,this.m_prefixName + "walking",this.m_walkSpeed,false);
        this.runAction(cc.sequence(this.m_nowAnimateAction,cc.callFunc(this.walkingCallFunc,this)));
        //this.runAction(cc.repeatForever(this.m_nowAnimateAction));
    },

    attackAnimate : function(enemyMonster){
        if(this.m_state == MonsterState.Attack){
            return;
        }
        this.m_state = MonsterState.Attack;
        this.startAnimate(this.m_attackAnimatePlist, this.m_attackAnimateAccount,this.m_prefixName + "attack",this.m_attackSpeed,false);
        var argu = {
            "enemyMonster" : enemyMonster,
            "myMonster" : this
        }
        this.runAction(cc.sequence(this.m_nowAnimateAction,cc.callFunc(this.attackCallFunc,this,argu)));

    },
    deathAnimate : function(enemyMonster)
    {
        if(this.m_state == MonsterState.Death){
            return;
        }
        this.m_state = MonsterState.Death;
        this.startAnimate(this.m_deathAnimatePlist, this.m_deathAnimateAccount,this.m_prefixName + "death",1,false);
        this.runAction(cc.sequence(this.m_nowAnimateAction,cc.callFunc(this.deathCallFunc,this)));
    },

    walkingLeftAnimate : function (enemyMonster) {
        if(this.m_state == MonsterState.WalkingLeft){
            return;
        }
        this.m_state = MonsterState.WalkingLeft;
        this.startAnimate(this.m_walkingAnimatePlist, this.m_walkingAnimateAccount,this.m_prefixName + "walking",this.m_walkSpeed,true);
        this.runAction(cc.sequence(this.m_nowAnimateAction,cc.callFunc(this.walkingCallFunc,this)));
    },

    monsterAction : function(state,enemyMonster){
        if(state == MonsterState.WalkingLeft){
            this.walkingLeftAnimate(enemyMonster)
        }
        else if(state == MonsterState.Attack){
            this.attackAnimate(enemyMonster);
        }
        else if(state == MonsterState.WalkingRight){
            this.walkingAnimate(enemyMonster);
        }
        else if(state == MonsterState.Death){
            this.deathAnimate(enemyMonster);
        }
    },

    //添加血条
    addBooldProgressTimer : function () {
        var backgroundSprite = cc.Sprite.create(res.GM_BackgroundBolld_png,cc.rect(0,0,this.width*0.8,10));
        backgroundSprite.setPosition(this.width/2.0,this.height);
        backgroundSprite.setContentSize(this.width*0.8,10);
        this.addChild(backgroundSprite);
        var booldSprite ;
        if(this.m_isMyMonster){
            booldSprite = cc.Sprite.create(res.GM_RedBlood_png,cc.rect(0,0,this.width*0.8,10));
        }
        else{
            booldSprite = cc.Sprite.create(res.GM_BlueBlood_png,cc.rect(0,0,this.width*0.8,10))
        }
        this.m_booldProgressTimer =  cc.ProgressTimer.create(booldSprite);
        /*if(this.m_isMyMonster){
            //this.m_boold.setReverseDirection(true);
        }*/
        this.m_booldProgressTimer.setPosition(this.width/2.0,this.height);
        this.m_booldProgressTimer.type = cc.ProgressTimer.TYPE_BAR;
        this.m_booldProgressTimer.setMidpoint(cc.p(0.0,0.5));
        this.m_booldProgressTimer.setBarChangeRate(cc.p(1.0,0.0));
        this.m_booldProgressTimer.setPercentage(80);
        this.addChild(this.m_booldProgressTimer);
    },
    update:function (dt){
        var num = this.m_HP / this.m_total_HP * 100;
        //cc.log(this.m_total_HP);
        this.m_booldProgressTimer.setPercentage(this.m_HP / this.m_total_HP * 100);
    }

});
