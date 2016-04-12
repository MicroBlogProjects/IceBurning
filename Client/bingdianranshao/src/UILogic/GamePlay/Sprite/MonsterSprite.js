/**
 * Created by jiachen on 2016/4/1.
 */

MonsterSprite = cc.Sprite.extend({
    m_weiyi : null,
    m_isMyMonster : true, //是否是我方怪物
    m_state :null, //执行什么动画
    m_type : null, //怪物还是建筑
    m_activity :true, //是否可以去除  死亡的时候依旧不能去除

    //用来计算当前的层级结构的
    m_frontMonsterSprite : null,  //前面
    m_nextMonsterSprite : null, //后面
    m_localZOrder : null,

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

    m_attackConfig : null,
    m_walkingConfig : null,
    m_deathConfig : null,
    m_skillConfig : null,

    //血条
    m_booldProgressTimer :null,
    m_total_HP :null,

    ctor : function(config,isMyMonster){
        this.m_weiyi = parseInt(Math.random() * 1000);
        var attributeConfig = config.attribute;
        this._super(attributeConfig.defaultImage);

        //设置属性
        this.m_id = attributeConfig.id;
        this.m_name = attributeConfig.name;
        this.m_walkSpeed = attributeConfig.walkSpeed;
        this.m_HP = attributeConfig.HP;
        this.m_total_HP = this.m_HP;
        this.m_sightRadius = attributeConfig.sightRadius;
         this.m_defense = attributeConfig.defense;
        this.m_attack = attributeConfig.attack;
        this.m_attackRadius = attributeConfig.attackRadius;
        this.m_isMyMonster = isMyMonster
        this.setDirect();
        this.scheduleUpdate();

        if(this.m_id >= 100){
            this.m_type = MonsterType.Building;
        }
        else{
            this.m_type = MonsterType.Animal
        }

        this.m_attackConfig = config.attack;
        this.m_walkingConfig = config.walking;
        this.m_deathConfig = config.death;
        this.m_skillConfig = config.skill;

        this.addBooldProgressTimer();
    },

    setDirect : function(){
        if(GC.IS_HOST){
            if(this.m_isMyMonster){
                this.m_direct = 1;
            }
            else{
                this.m_direct = -1;
            }
        }
        else {
            if(this.m_isMyMonster){
                this.m_direct = -1;
            }
            else {
                this.m_direct = 1;
            }
        }
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
        if(this.m_type == MonsterType.Animal){
            if(this.m_direct == -1){
                this.setFlippedX(true);
            }
            else if(this.m_direct == 1){
                this.setFlippedX(false);
            }
        }

        var speed = totalTime * 1.0 / account;
        var animation = new cc.Animation(animFrames, speed);
        this.m_nowAnimateAction = new cc.Animate(animation);
    },

    deathCallFunc : function(){
        this.m_activity = false;
        this.removeFromParent();
    },

    attackCallFunc : function(sprite,argu){
        var enemyMonster = argu.enemyMonster;
        var myMonster = argu.myMonster;
        var skillConfig = argu.skillConfig;
        var endAnimate = argu.endAnimate;
        if(skillConfig == null || skillConfig == undefined){
            enemyMonster.m_HP -= myMonster.m_attack * 1.0 / enemyMonster.m_defense +1;//至少一点伤害
        }
        else {
            monsterBackGroundLayer.skillAnimate(skillConfig,enemyMonster);
        }
        if(endAnimate == null || endAnimate == undefined){
            this.m_state = null;
        }
        else {
            this.startAnimate(endAnimate);
            this.runAction(cc.sequence(this.m_nowAnimateAction,cc.callFunc(this.attackEndCallFunc,this)));
        }

    },
    attackEndCallFunc :function(){
        this.m_state = null;
    },
    walkingCallFunc : function(){
        this.m_state = null;
    },
    stopAnimate : function(){
        this.stopAllActions();
    },

    walkingAnimate :function(state){
        if(this.m_type == MonsterType.Building){
            return;
        }
        if (this.m_state == state){
            return;
        }
        this.m_state =state;
        this.startAnimate(this.m_walkingConfig.begin);
        this.runAction(cc.sequence(this.m_nowAnimateAction,cc.callFunc(this.walkingCallFunc,this)));
    },

    attackAnimate : function(state,enemyMonster){
        if(this.m_state == state){
            return;
        }
        this.m_state = state;
        var beginConfig = this.m_attackConfig.begin;
        this.startAnimate(beginConfig);
        var endConfig = this.m_attackConfig.end;
        var skillConfig = this.m_skillConfig;
        var argu = {
            "enemyMonster" : enemyMonster,
            "myMonster" : this,
            "endAnimate" : endConfig,
            "skillConfig" : skillConfig
        }
        this.runAction(cc.sequence(this.m_nowAnimateAction,cc.callFunc(this.attackCallFunc,this,argu)));

    },
    deathAnimate : function(state) {
        if(this.m_state == state){
            return;
        }
        this.m_state = state;
        this.startAnimate(this.m_deathConfig.begin);
        this.runAction(cc.sequence(this.m_nowAnimateAction,cc.callFunc(this.deathCallFunc,this)));
    },


    monsterAction : function(state,enemyMonster){
        if(state == MonsterState.WalkingLeft){
            this.m_direct = -1;
            this.walkingAnimate(state)
        }
        else if(state == MonsterState.WalkingRight){
            this.m_direct = 1;
            this.walkingAnimate(state)
        }
        else if(state == MonsterState.AttackLeft){
            this.m_direct = -1;
            this.attackAnimate(state,enemyMonster)
        }
        else if(state == MonsterState.AttackRight){
            this.m_direct = 1;
            this.attackAnimate(state,enemyMonster)
        }
        else if(state == MonsterState.Death){
            this.deathAnimate(state);
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
        this.m_booldProgressTimer.setPosition(this.width/2.0,this.height);
        this.m_booldProgressTimer.type = cc.ProgressTimer.TYPE_BAR;
        this.m_booldProgressTimer.setMidpoint(cc.p(0.0,0.5));
        this.m_booldProgressTimer.setBarChangeRate(cc.p(1.0,0.0));
        this.m_booldProgressTimer.setPercentage(80);
        this.addChild(this.m_booldProgressTimer);
    },
    update:function (dt){
        var num = this.m_HP / this.m_total_HP * 100;
        this.m_booldProgressTimer.setPercentage(this.m_HP / this.m_total_HP * 100);
    }

});
