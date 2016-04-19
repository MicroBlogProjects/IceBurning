/**
 * Created by jiachen on 2016/4/11.
 */

var monsterManager;
var MonsterManager = cc.Class.extend({

    //用户添加Monster模块
    myMainBuildingSprite : null,
     enemyMainBuildingSprite : null,
     myMonsterArray : null, //用来存放我方怪物，包括怪物，建筑类
     enemyMonsterArray : null,

    //层级管理模块
    headMonsterSprite : null,

    ctor : function(){

        //用户添加Monster模块
        this.myMonsterArray = []; //创建一个数组
         this.enemyMonsterArray = [];

        //层级管理模块
        this.headMonsterSprite = new MonsterSprite(MonsterConfig[""+2]);
        this.headMonsterSprite.setPosition(0,7000);
        this.headMonsterSprite.getPosition();
        this.headMonsterSprite.m_localZOrder = 0;
        monsterManager = this;
    },

    getTime : function(){
        var mydate = new Date();
        cc.log("minues :"+mydate.getMinutes() +"seconds"+ mydate.getSeconds()+ "millise"+mydate.getMilliseconds());
    },

    //用户添加Monster模块
    addMonsterSprite : function(id, point, isMyMonster){
        /*cc.log("add monster!!!!!!!!!" + id);
        this.getTime();*/
        var config = MonsterConfig[""+id];
        if(config.attribute.id < 100){//怪物
            var mosterSprite = new MonsterSprite(config,isMyMonster);
                mosterSprite.setPosition(point);
                monsterLayer.addMonsterSprite(mosterSprite);
                if(isMyMonster){
                    this.myMonsterArray.push(mosterSprite);
                }
                else{
                    this.enemyMonsterArray.push(mosterSprite);
                }
                this.addHierarchyMonsterSprite(mosterSprite);
            }
        else { //建筑物
                var mosterSprite = new MonsterSprite(config,isMyMonster);
                mosterSprite.setPosition(point);
                monsterLayer.addMonsterSprite(mosterSprite);
                if(isMyMonster){
                    this.myMonsterArray.push(mosterSprite);
                }
                else{
                    this.enemyMonsterArray.push(mosterSprite);
                }
                this.addHierarchyMonsterSprite(mosterSprite);
        }
     },
    //更新Monster
    updateMonsterData : function(){
        this.updateMonsterArray()
        this.monsterWalking();
    },

    //删除已经死亡的怪物
    updateMonsterArray :function(){
        for(var  i = 0; i < this.myMonsterArray.length; i++){
            var monster = this.myMonsterArray[i];
            if(monster.m_activity == false){
                this.removeMonsterSprite(monster);
                this.myMonsterArray.splice(i,1);
            }
        }
        for(var  i = 0; i < this.enemyMonsterArray.length;i ++){
            var monster = this.enemyMonsterArray[i];
            if(this.enemyMonsterArray[i].m_activity == false){
                this.removeMonsterSprite(monster);
                this.enemyMonsterArray.splice(i,1);
            }
        }
    },
    //怪物行走动画
    monsterWalking :function(){
        for(var i = 0;i < this.myMonsterArray.length; i++){
            var  myMonster = this.myMonsterArray[i];
            this.walk(myMonster,this.enemyMonsterArray);
        }
        for(var i = 0;i < this.enemyMonsterArray.length; i++){
            var  myMonster = this.enemyMonsterArray[i];
            this.walk(myMonster,this.myMonsterArray);
        }
    },

    walk : function(monster, enemyMonsterArray){
        if(monster.m_HP <= 0){
            //this.resetBuildingPosition(monster);
            checkPathManager.resetBuildingPosition(monster);
            monster.monsterAction(MonsterState.Death);
            return;
        }

        var sighRadius = monster.m_sightRadius;
        var attackRadius = monster.m_attackRadius;
        var monsterPoint = monster.getPosition();

        var destinationMonster = null;
        var minDistance  = sighRadius * sighRadius; //视野范围内

        for(var i = 0; i < enemyMonsterArray.length; i++){ //寻找最近的敌人
            var enemyMonster = enemyMonsterArray[i];
            if(enemyMonsterArray.m_HP <= 0){ //血量为0
                continue;
            }

            var enemyPoint = enemyMonster.getPosition();
            var distance = this.getPointDistance(monsterPoint,enemyPoint);
            if (distance < minDistance){
                minDistance = distance  ;
                destinationMonster = enemyMonster;
            }
        }

        var destinationX;
        var destinationY;
        var destinationPoint;
        var state;
        if (destinationMonster == null){ //视野内没有任何敌人 向前走
            monster.setDirect();
            if(GC.IS_HOST){
                if(monster.m_isMyMonster){
                    state = MonsterState.WalkingRight;
                }
                else{
                    state = MonsterState.WalkingLeft;
                }
            }
            else{
                if(monster.m_isMyMonster){
                    state = MonsterState.WalkingLeft;
                }
                else {
                    state = MonsterState.WalkingRight;
                }

            }
            if(checkPathManager.isInFightUpPath(monsterPoint)){
                destinationX = monsterPoint.x;
                destinationY = monsterPoint.y + monster.m_walkSpeed * ScheduleTime * monster.m_direct;
                destinationPoint = cc.p(destinationX,destinationY);
                if(!checkPathManager.isInFightPath(destinationPoint)){
                    destinationX = monsterPoint.x + monster.m_walkSpeed * ScheduleTime * monster.m_direct;
                    destinationY = monsterPoint.y;
                    destinationPoint = cc.p(destinationX,destinationY);
                }
            }
            else if(checkPathManager.isInFightDownPath(monsterPoint)){
                destinationX = monsterPoint.x;
                destinationY = monsterPoint.y - monster.m_walkSpeed * ScheduleTime * monster.m_direct;
                destinationPoint = cc.p(destinationX,destinationY);
                if(!checkPathManager.isInFightPath(destinationPoint)){
                    destinationX = monsterPoint.x + monster.m_walkSpeed * ScheduleTime * monster.m_direct;
                    destinationY = monsterPoint.y;
                    destinationPoint = cc.p(destinationX,destinationY);
                }
            }
            else {
                destinationX = monsterPoint.x + monster.m_walkSpeed * ScheduleTime * monster.m_direct;
                destinationY = monsterPoint.y;
                destinationPoint = cc.p(destinationX,destinationY);
            }
            monster.setPosition(destinationPoint);
            if(destinationY != monsterPoint.y)
            {
                this.monsterChangeY(monster);
            }
        }
        else{
            var enemyPoint = destinationMonster.getPosition();
            if(minDistance < (attackRadius * attackRadius)){ //攻击范围
                if(monsterPoint.x < enemyPoint.x){
                    state = MonsterState.AttackRight;
                }
                else{
                    state = MonsterState.AttackLeft;
                }
            }
            else{
                var dx = monsterPoint.x - enemyPoint.x;
                var dy = monsterPoint.y - enemyPoint.y;
                if(dx ==0){
                    if(dy > 0) //正下方
                    {
                    }
                    else{//正上方
                    }
                }
                else{
                    var d = monster.m_walkSpeed * ScheduleTime;
                    var ratio = dy / dx;
                    var x = Math.sqrt((d * d * 1.0) / (ratio * ratio +1));
                    var y = Math.sqrt((d * d - x * x));
                    if(dx < 0){
                        state = MonsterState.WalkingRight;
                        destinationX = monsterPoint.x + x;
                    }
                    else{
                        destinationX = monsterPoint.x - x;
                        state = MonsterState.WalkingLeft
                    }
                    if(dy < 0){
                        destinationY  =monsterPoint.y + y;
                    }
                    else{
                        destinationY  =monsterPoint.y - y;
                    }
                    destinationPoint = cc.p(destinationX,destinationY);
                    monster.setPosition(destinationPoint);
                    if(destinationY != monsterPoint.y){
                        this.monsterChangeY(monster);
                    }

                }
            }
        }
        monster.monsterAction(state,destinationMonster);
    },

    getPointDistance : function (p1, p2) {
        return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
    },

    //用来计算范围伤害
    getMonstersInRect : function(point, radius){
        var radius2 = radius * radius;
        var monsters = [];
        for(var i = 0; i < this.enemyMonsterArray.length; i++){
            var enemyMonster = this.enemyMonsterArray[i];
            if(this.getPointDistance(enemyMonster.getPosition(),point) <= radius2){
                monsters.push(enemyMonster);
            }
        }
        return monsters;
    },


    //层级管理模块
    //层级管理模块添加Monster
    addHierarchyMonsterSprite : function (monsterSprite) {
        var indexMonster = this.headMonsterSprite;
        var nextMonster  = this.headMonsterSprite.m_nextMonsterSprite;
        var position = monsterSprite.getPosition();
        while(nextMonster != null && nextMonster != undefined){
            var nextPosition = nextMonster.getPosition();
            if(nextPosition.y > position.y ){//向下顺移
                indexMonster = nextMonster;
                nextMonster = indexMonster.m_nextMonsterSprite;
            }
            else {
                break;
            }
        }

        indexMonster.m_nextMonsterSprite = monsterSprite;
        monsterSprite.m_frontMonsterSprite = indexMonster;
        monsterSprite.m_nextMonsterSprite = nextMonster;
        if(nextMonster != null && nextMonster !=undefined) {
            nextMonster.m_frontMonsterSprite = monsterSprite;
        }
        monsterSprite.m_localZOrder = indexMonster.m_localZOrder + 1;
        monsterSprite.setLocalZOrder(monsterSprite.m_localZOrder);
        this.updataLocalZOrder(this.headMonsterSprite.m_nextMonsterSprite);

    },
    //更新Z轴
    updataLocalZOrder : function(monsterSprite){
        var localZOrder ;
        if(monsterSprite.m_frontMonsterSprite == null || monsterSprite.m_frontMonsterSprite == undefined){
            localZOrder = 0;
        }
        else {
            localZOrder = monsterSprite.m_frontMonsterSprite.m_localZOrder;
        }
        while(monsterSprite != null && monsterSprite != undefined){
            localZOrder ++;
            monsterSprite.m_localZOrder = localZOrder;
            monsterSprite.setLocalZOrder(localZOrder);
            monsterSprite = monsterSprite.m_nextMonsterSprite;
        }
    },
    //当Y轴改变
    monsterChangeY : function(monster){
        var frontMonster = monster.m_frontMonsterSprite;
        var nextMonster = monster.m_nextMonsterSprite;
        frontMonster.m_nextMonsterSprite = nextMonster;
        monster.m_frontMonsterSprite = null;
        monster.m_nextMonsterSprite = null;
        if(nextMonster != null && nextMonster != undefined){
            nextMonster.m_frontMonsterSprite = frontMonster;
        }
        this.addHierarchyMonsterSprite(monster);
        /*var position = monster.getPosition();
        var frontMonster = monster.m_frontMonsterSprite;
        if(frontMonster == null || frontMonster == undefined){
            cc.log("monster.frontmonster is num " + monster.m_weiyi);
            return;
        }
        var frontMonsterPosition = frontMonster.getPosition();
        while(frontMonsterPosition.y < position.y){//上一个monstery比较小
            this.exchangeMonsters(frontMonster,monster);

            //继续向前走
            frontMonster = monster.m_frontMonsterSprite;
            if(frontMonster == null || frontMonster == undefined){
                break;
            }
            frontMonsterPosition = frontMonster.getPosition();
        }

        var nextMonster = monster.m_nextMonsterSprite;
        if(nextMonster == null || nextMonster == undefined){
            return;
        }
        var nextMonsterPosition = nextMonster.getPosition();

        while(nextMonsterPosition.y > position.y){ //下一个monster比较大
            this.exchangeMonsters(monster,nextMonster);
            nextMonster = monster.m_nextMonsterSprite;
            if(nextMonster == null || nextMonster == undefined){
                break;
            }
            nextMonsterPosition = nextMonster.getPosition();
        }*/
    },
    //交换2个Monster
    exchangeMonsters : function(frontMonster,monster){

        frontMonster.m_frontMonsterSprite.m_nextMonsterSprite = monster;
        if(monster.m_nextMonsterSprite != null && monster.m_nextMonsterSprite != undefined){
            monster.m_nextMonsterSprite.m_frontMonsterSprite = frontMonster;
        }
        frontMonster.m_nextMonsterSprite = monster.m_nextMonsterSprite;
        monster.m_frontMonsterSprite = frontMonster.m_frontMonsterSprite;
        frontMonster.m_frontMonsterSprite = monster;
        if(monster.m_nextMonsterSprite != null && monster.m_nextMonsterSprite != undefined){
            monster.m_nextMonsterSprite = frontMonster;
        }


        //交换
        var temp = frontMonster.m_localZOrder;
        frontMonster.m_localZOrder = monster.m_localZOrder;
        monster.m_localZOrder = temp;
        frontMonster.setLocalZOrder(frontMonster.m_localZOrder);
        monster.setLocalZOrder(monster.m_localZOrder);
    },
    //yichuMonster
    removeMonsterSprite : function(monster){
        var frontMonster = monster.m_frontMonsterSprite;
        var nextMonster = monster.m_nextMonsterSprite;
        frontMonster.m_nextMonsterSprite = nextMonster;
        if(nextMonster != null && nextMonster != undefined){
            nextMonster.m_frontMonsterSprite = frontMonster;
        }
        monster.m_nextMonsterSprite = null;
        monster.m_frontMonsterSprite = null;
    }


});