/**
 * Created by jiachen on 2016/4/10.
 */

//带弧线的远程攻击
var RangedAttackSprite = cc.Sprite.extend({
    m_attack : null,
    m_time : null,
    m_attackRadius : null,
    m_attackAnimate :null,
    m_frontPoint : null,
    m_PAI : null,
    m_runAnimate : null,
    m_isRangeAttack : true,
    m_isArcAnimate : null,
    m_enemyMonster : null,
    m_Camp:null,
    ctor : function(config, position,enemyMonster){
        var attributeConfig = config.attribute;
        this._super(attributeConfig.defaultImage);

        this.m_Camp = 1 - enemyMonster.m_Camp; 
        this.m_enemyMonster = enemyMonster;
        this.m_attack = attributeConfig.attack;
        this.m_time = attributeConfig.time;
        this.m_attackRadius = attributeConfig.attackRadius;
        this.m_isRangeAttack = attributeConfig.isRangeAttack;
        this.m_isArcAnimate = attributeConfig.isArcAnimate;
        this.m_attackConfig = config.attackAnimate;
        var offsetPoint = attributeConfig.offsetPoint;
        this.setPosition(position.x + offsetPoint.x, position.y + offsetPoint.y);
        this.m_frontPoint = this.getPosition();
        this.m_runAnimate = config.Animate;


        if(GC.IS_HOST){
            if(this.m_enemyMonster.m_isMyMonster == true){
                this.setFlippedX(true);
            }
            else{
                this.setFlippedX(false);
            }
        }
        else {
            if(this.m_enemyMonster.m_isMyMonster == true){
                this.setFlippedX(false);
            }
            else{
                this.setFlippedX(true);
            }
        }
        this.m_PAI = 2*Math.asin(1);

    },

    startAnimate : function(){
        if(this.m_isArcAnimate){
            this.startArcAnimate();
        }
        else {
            this.startStraightAnimate();
        }
    },

    startStraightAnimate : function(){
        this.schedule(this.straight,0);
    },

    straight : function(){
        if(this.m_enemyMonster.m_activity == false){
            this.removeFromParent();
            return;
        }
        this.setSlope();
        var walkSpeed = 300;
        var des_point = this.m_enemyMonster.getPosition();
        var position = this.getPosition();
        var distance = (des_point.x - position.x) * (des_point.x - position.x) + (des_point.y - position.y) * (des_point.y - position.y);
        var destinationX = position.x;
        var destinationY = position.y;
        var d = walkSpeed * 1/60;
        var destinationPoint;
        if(distance <= this.width * this.width * 0.5){
            this.calculationsDamage();
            this.removeFromParent();
            return;
        }
        else {
            var dx = position.x - des_point.x;
            var dy = position.y - des_point.y;
            if(dx ==0){
                if(dy > 0) //正下方
                {
                    destinationY = position.y - d;
                }
                else{//正上方
                    destinationY = position.y + d;
                }
            }
            else{
                var ratio = dy / dx;
                var x = Math.sqrt((d * d * 1.0) / (ratio * ratio +1));
                var y = Math.sqrt((d * d - x * x));
                if(dx < 0){
                    destinationX = position.x + x;
                }
                else{
                    destinationX = position.x - x;
                }
                if(dy < 0){
                    destinationY  =position.y + y;
                }
                else{
                    destinationY  =position.y - y;
                }
            }
            destinationPoint = cc.p(destinationX,destinationY);
            var moveTo = new cc.MoveTo(1/60,destinationPoint);
            this.runAction(moveTo);
        }
    },


    startArcAnimate : function(){
        if(this.m_enemyMonster.m_activity == false){
            this.removeFromParent();
            return;
        }
        var point = this.m_enemyMonster.getPosition();
        this.schedule(this.setSlope,0);
        var bezierToAnimate = this.getBezierAnimate(point);
        if(this.m_runAnimate == null || this.m_runAnimate == undefined){
            this.runAction(cc.sequence(bezierToAnimate,cc.callFunc(this.animateCallFunc,this,null)));
        }
        else {
            var argu = {
                "end" : this.m_runAnimate.end,
                "effect" : this.m_runAnimate.effect
            };
            var runAnimate = this.getRunanimate(this.m_runAnimate.begin);
            var action = new cc.Spawn(bezierToAnimate,runAnimate);
            this.runAction(cc.sequence(action,cc.callFunc(this.animateCallFunc,this,argu)));
        }
    },

    getBezierAnimate : function(point){
        var beginPoint = this.getPosition();
        var endPoint = point;
        var maxY;
        if(beginPoint.y > endPoint.y){
            maxY = beginPoint.y;
        }
        else {
            maxY = endPoint.y;
        }
        var mindlePoint = cc.p( (beginPoint.x  + endPoint.x) / 2, maxY + 100);
        var bezierTo = new cc.BezierTo(0.5,[beginPoint,mindlePoint,endPoint]);
        return bezierTo;
    },

    getRunanimate : function(config){
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
        return new cc.Animate(animation);
    },


    setSlope : function(){
        var nowPosition = this.getPosition();
        var dx = nowPosition.x - this.m_frontPoint.x;
        var dy = nowPosition.y - this.m_frontPoint.y;
        if(dx == 0){
            return;
        }
        this.m_frontPoint = nowPosition;
        var slope = 360-180 * Math.atan(dy/dx)/this.m_PAI;
        this.setRotation(slope);
    },

    animateCallFunc : function(sender,argu){
        if(argu == null || argu == undefined){
            sender.calculationsDamage();
            sender.removeFromParent();
            return;
        }
        if(argu.effect == null || argu.effect == undefined){
            cc.log("callfunc3");
            //sender.calculationsDamage();
        }
        else {
            var position =cc.p(sender.getPosition().x,sender.getPosition().y);
            monsterLayer.rangedAttackEffect(argu.effect,position);
        }
        if(argu.end == null || argu.end == undefined){
            sender.calculationsDamage();
            sender.removeFromParent();
        }
        else {
            var action = this.getRunanimate(argu.end);
            this.runAction(cc.sequence(action,cc.callFunc(this.animateEndCallFunc,this)));
        }
    },

    animateEndCallFunc : function(sender){
        sender.removeFromParent();
    },

    calculationsDamage : function(){
        if(this.m_isRangeAttack){
            var monsters = monsterManager.getMonstersInRect(1-this.m_Camp,monsterBackGroundLayer.StaggeredCoordForPosition(this.getPosition()), this.m_attackRadius);
            for(var i = 0; i < monsters.length ;i++){
                var monster = monsters[i];
                monster.m_HP -= (this.m_attack / monster.m_defense + 1);
            }
        }
        else {
            if(this.m_enemyMonster.m_activity == false){
                return;
            }
            if(this.m_enemyMonster.m_HP <=0 ){
                return;
            }
            this.m_enemyMonster.m_HP -=(this.m_attack / this.m_enemyMonster.m_defense + 1);
        }
    }
});