/**
 * Created by jiachen on 2016/3/29.
 */

//管理所有的怪物
var ScheduleTime =1.0/10
var monsterManager;

var MonsterBackgroundLayer = cc.Layer.extend({
    myMonsterArray : null,
    enemyMonsterArray : null,
    //schedule : null,
    ctor : function(){
        this._super();
        this.myMonsterArray = []; //创建一个数组
        this.enemyMonsterArray = [];
        monsterManager = this;

        //this.schedule(this.update,1.0/6); //计时器
        this.schedule(this.updateEvent,ScheduleTime);
    },

    addMonsterSprite : function(config, point, type){
        var mosterSprite;
        if(type == MonsterType.OwnMonster){
            mosterSprite = new MonsterSprite(config,true);
        }
        else{
            mosterSprite = new MonsterSprite(config,false);
        }
        mosterSprite.setPosition(point);
        this.addChild(mosterSprite);
        mosterSprite.walkingAnimate();
        if(type == MonsterType.OwnMonster)
            this.myMonsterArray.push(mosterSprite);
        else{
            this.enemyMonsterArrayp.push(mosterSprite);
        }
    },

    test : function(config, point){
        for(var i = 0; i < 10; i++){
            var randownum = Math.floor(Math.random() * 10000+1);
            var mosterSprite = new MonsterSprite(config,false);
            mosterSprite.setPosition(new cc.Point(randownum %(GC.w) + GC.w,randownum%640));
            this.addChild(mosterSprite);
            mosterSprite.walkingAnimate(mosterSprite);
            this.enemyMonsterArray.push(mosterSprite);
        }
        for(var i =0; i< 10; i++){
            var randownum = Math.floor(Math.random() * 10000+1);
            var mosterSprite = new MonsterSprite(config,true);
            mosterSprite.setPosition(new cc.Point(randownum %(GC.w),randownum%640));
            this.addChild(mosterSprite);
            mosterSprite.walkingAnimate();
            this.myMonsterArray.push(mosterSprite);
        }

    },

    updateEvent : function(){
        this.updateMonsterArray()
        this.monsterWalking();
    },

    updateMonsterArray :function(){
        for(var  i = 0; i < this.myMonsterArray.length; i++){
            var monster = this.myMonsterArray[i];
            if(monster.m_activity == false){
                this.myMonsterArray.splice(i,1);
            }
        }
        for(var  i = 0; i < this.enemyMonsterArray.length;i ++){
            var monster = this.enemyMonsterArray[i];
            if(this.enemyMonsterArray[i].m_activity == false){
                this.enemyMonsterArray.splice(i,1);
            }
        }
        //cc.log("111");
    },

    monsterWalking :function(){
        for(var i = 0;i < this.myMonsterArray.length; i++){
            var  myMonster = this.myMonsterArray[i];
            this.walk(myMonster,this.enemyMonsterArray,true);
        }
        for(var i = 0;i < this.enemyMonsterArray.length; i++){
            var  myMonster = this.enemyMonsterArray[i];
            this.walk(myMonster,this.myMonsterArray,false);
        }

    },

    walk : function(monster, monsterArray, ismyMonster){
        if(monster.m_HP <= 0){
            monster.monsterAction(MonsterState.Death);
            return;
        }

        var point = monster.getPosition();
        var sighRadius = monster.m_sightRadius;
        var attackRadius = monster.m_attackRadius;
        var des_x;
        var des_y = point.y;
        var state
        if(ismyMonster){
            des_x = point.x +  MonsterStep / monster.m_walkSpeed * ScheduleTime;
            state = MonsterState.WalkingRight;
        }
        else{
            des_x = point.x -  MonsterStep / monster.m_walkSpeed * ScheduleTime;
            state = MonsterState.WalkingLeft;
        }
        var min_distance = sighRadius * sighRadius;;
        var des_enemyMonster = monsterArray[0];
        for(var i = 0;i <monsterArray.length ;i++){
            var enemyMonster = monsterArray[i];
            if(enemyMonster.m_HP < 0){
                continue;
            }
            var enemyPoint = enemyMonster.getPosition();
            var enemyPoint_x = enemyPoint.x - point.x;
            var enemyPoint_y = enemyPoint.y - point.y;
            var distance = enemyPoint_x * enemyPoint_x + enemyPoint_x * enemyPoint_x;
            if (distance > min_distance) {
                continue;
            }
            else {
                min_distance = distance;
                des_enemyMonster =enemyMonster;
                if(distance > attackRadius * attackRadius ){//大于攻击范围
                    var d = MonsterStep / monster.m_walkSpeed * ScheduleTime;
                    var ratio = enemyPoint_x / enemyPoint_y;
                    var y = Math.sqrt(d*d /((ratio+1) *(ratio+1)));
                    var x = Math.sqrt((ratio*ratio *d *d)/(ratio*ratio+1));
                    if(enemyPoint_x < 0){
                        if(ismyMonster){
                            state = MonsterState.WalkingLeft;
                        }
                        else{
                            state = MonsterState.WalkingRight;
                        }
                        x*=-1;
                    }
                    if(enemyPoint_y < 0){
                        y*=-1;
                    }
                    des_x = point.x + x;
                    des_y = point.y + y;
                }
                else{//正在攻击
                    state = MonsterState.Attack;
                    des_x = point.x;
                    des_y = point.y;

                }
            }
        }
        monster.monsterAction(state,des_enemyMonster);
        monster.setPosition(new cc.Point(des_x,des_y));
    }
});