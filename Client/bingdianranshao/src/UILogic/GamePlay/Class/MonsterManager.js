/**
 * Created by jiachen on 2016/4/11.
 */

var monsterManager;
var account = 1;
var numOfSprite = 0;
var MonsterManager = cc.Class.extend({

    //用户添加Monster模块
    myMainBuildingSprite : null,
     enemyMainBuildingSprite : null,
     MonsterArray : null, //用来存放我方怪物，包括怪物，建筑类
    //层级管理模块
    headMonsterSprite : null,

    ctor : function(){

        //用户添加Monster模块
        this.MonsterArray={};
        this.MonsterArray[0]=[];
        this.MonsterArray[1]=[];
        //层级管理模块
        this.headMonsterSprite = new MonsterSprite(MonsterConfig.yuangujuren);
        this.headMonsterSprite.setPosition(0,7000);
        this.headMonsterSprite.getPosition();
        this.headMonsterSprite.m_localZOrder = 0;
        monsterManager = this;
    },

    //用户添加Monster模块
    addMonsterSprite : function(id, point, isMyMonster)
    {

        var config = MonsterConfig[id];
        if(config.attribute.id < 100)
        {//怪物
            var mosterSprite = new MonsterSprite(config,isMyMonster);
                mosterSprite.m_spriteID = numOfSprite++;
                mosterSprite.setMyPosition(point);
                monsterLayer.addMonsterSprite(mosterSprite);
                if(isMyMonster)
                {
                    mosterSprite.m_Camp = 0;
                    this.MonsterArray[0].push(mosterSprite);
                }
                else
                {
                    mosterSprite.m_Camp = 1;
                    this.MonsterArray[1].push(mosterSprite);
                }
            mosterSprite.m_weiyi = account;
            account ++;
            this.addHierarchyMonsterSprite(mosterSprite);
        }
        else { //建筑物
                var mosterSprite = new MonsterSprite(config,isMyMonster);
                mosterSprite.setMyPosition(point);
                monsterLayer.addMonsterSprite(mosterSprite);
                if(isMyMonster){
                    mosterSprite.m_Camp = 0;
                    this.MonsterArray[0].push(mosterSprite);
                }
                else{
                    mosterSprite.m_Camp = 1;
                    this.MonsterArray[1].push(mosterSprite);
                }
            mosterSprite.m_weiyi = account;
            account ++;
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
        for(var camp = 0; camp < 2; ++ camp)
            for(var  i = 0; i < this.MonsterArray[camp].length; i++){
                var monster = this.MonsterArray[camp][i];
                if(monster.m_activity == false)
                {
                    this.removeMonsterSprite(monster);
                    this.MonsterArray[camp].splice(i,1);
                }
            }
    },
    //怪物行走动画
    monsterWalking :function()
    {
        for(var camp = 0; camp < 2; ++ camp)
        {
            for(var i = 0;i < this.MonsterArray[camp].length; i++)
            {
                var  myMonster = this.MonsterArray[camp][i];
                this.walk(myMonster,this.MonsterArray[1-camp]);
            }
        }
    },

    walk : function(monster, MonsterArray)
    {
        if(monster.m_HP <= 0)
        {
            monster.monsterAction(MonsterState.Death);
            return;
        }
        algorithmOfStatus.GetNextLocation(monster);
     /* if (destinationMonster == null)
        { //视野内没有任何敌人 向前走
            monster.setDirect();
            if(GC.IS_HOST)
            {
                if(monster.m_isMyMonster)
                {
                    state = MonsterState.WalkingRight;
                }
                else
                {
                    state = MonsterState.WalkingLeft;
                }
            }
            else
            {
                if(monster.m_isMyMonster)
                {
                    state = MonsterState.WalkingLeft;
                }
                else 
                {
                    state = MonsterState.WalkingRight;
                }
            }
            if(checkPathManager.isInFightUpPath(monsterPoint))
            {
                destinationX = monsterPoint.x;
                destinationY = monsterPoint.y + monster.m_walkSpeed * ScheduleTime * monster.m_direct;
                destinationPoint = cc.p(destinationX,destinationY);
                if( !checkPathManager.isInFightPath( destinationPoint ) )
                {
                    destinationX = monsterPoint.x + monster.m_walkSpeed * ScheduleTime * monster.m_direct;
                    destinationY = monsterPoint.y;
                    destinationPoint = cc.p(destinationX, destinationY);
                }
            }
            else if(checkPathManager.isInFightDownPath(monsterPoint))
            {
                destinationX = monsterPoint.x;
                destinationY = monsterPoint.y - monster.m_walkSpeed * ScheduleTime * monster.m_direct;
                destinationPoint = cc.p(destinationX,destinationY);
                if(!checkPathManager.isInFightPath(destinationPoint))
                {
                    destinationX = monsterPoint.x + monster.m_walkSpeed * ScheduleTime * monster.m_direct;
                    destinationY = monsterPoint.y;
                    destinationPoint = cc.p(destinationX,destinationY);
                }
            }
            else 
            {
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
        else
        {
            var enemyPoint = destinationMonster.getPosition();
            if(minDistance < (attackRadius * attackRadius))
            { //攻击范围
                if(monsterPoint.x < enemyPoint.x)
                {
                    state = MonsterState.AttackRight;
                }
                else
                {
                    state = MonsterState.AttackLeft;
                }
            }
            else
            {
                var dx = monsterPoint.x - enemyPoint.x;
                var dy = monsterPoint.y - enemyPoint.y;
                if(dx ==0)
                {
                    if(dy > 0) //正下方
                    {
                    }
                    else
                    {//正上方
                    }
                }
                else
                {
                    var d = monster.m_walkSpeed * ScheduleTime;
                    var ratio = dy / dx;
                    var x = Math.sqrt((d * d * 1.0) / (ratio * ratio +1));
                    var y = Math.sqrt((d * d - x * x));
                    if(dx < 0)
                    {
                        state = MonsterState.WalkingRight;
                        destinationX = monsterPoint.x + x;
                    }
                    else
                    {
                        destinationX = monsterPoint.x - x;
                        state = MonsterState.WalkingLeft
                    }
                    if(dy < 0)
                    {
                        destinationY = monsterPoint.y + y;
                    }
                    else
                    {
                        destinationY = monsterPoint.y - y;
                    }
                    destinationPoint = cc.p(destinationX,destinationY);
                    monster.setPosition(destinationPoint);
                    if(destinationY != monsterPoint.y)
                    {
                        this.monsterChangeY(monster);
                    }

                }
            }
        }*/
        var state = null;
        var destinationMonster = null;
        monster.monsterAction(state,destinationMonster);
    },

    getPointDistance : function (p1, p2) 
    {
        return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
    },


    //层级管理模块
    //层级管理模块添加Monster
    addHierarchyMonsterSprite : function (monsterSprite) 
    {
        var indexMonster = this.headMonsterSprite;
        var nextMonster  = this.headMonsterSprite.m_nextMonsterSprite;
        var position = monsterSprite.getPosition();
        while(nextMonster != null && nextMonster != undefined)
        {
            var nextPosition = nextMonster.getPosition();
            if(nextPosition.y > position.y )
            {//向下顺移
                indexMonster = nextMonster;
                nextMonster = indexMonster.m_nextMonsterSprite;
            }
            else 
            {
                break;
            }
        }

        indexMonster.m_nextMonsterSprite = monsterSprite;
        monsterSprite.m_frontMonsterSprite = indexMonster;
        monsterSprite.m_nextMonsterSprite = nextMonster;
        if(nextMonster != null && nextMonster != undefined) 
        {
            nextMonster.m_frontMonsterSprite = monsterSprite;
        }
        monsterSprite.m_localZOrder = indexMonster.m_localZOrder + 1;
        monsterSprite.setLocalZOrder(monsterSprite.m_localZOrder);
        this.updataLocalZOrder(monsterSprite);
    },
    //更新Z轴
    updataLocalZOrder : function(monsterSprite)
    {
        var localZOrder ;
        if(monsterSprite.m_frontMonsterSprite == null || monsterSprite.m_frontMonsterSprite == undefined)
        {
            localZOrder = 0;
        }
        else 
        {
            localZOrder = monsterSprite.m_frontMonsterSprite.m_localZOrder;
        }
        while(monsterSprite != null && monsterSprite != undefined)
        {
            localZOrder ++;
            monsterSprite.m_localZOrder = localZOrder;
            monsterSprite.setLocalZOrder(localZOrder);
            monsterSprite = monsterSprite.m_nextMonsterSprite;
        }
    },
    //当Y轴改变
    monsterChangeY : function(monster)
    {/*
        var position = monster.getPosition();
        var frontMonster = monster.m_frontMonsterSprite;
        if(frontMonster == null || frontMonster == undefined)
        {
            cc.log("monster.frontmonster is num " + monster.m_weiyi);
            return;
        }
        var frontMonsterPosition = frontMonster.getPosition();
        while(frontMonsterPosition.y < position.y)
        {//上一个monstery比较小
            this.exchangeMonsters(frontMonster,monster);
            //继续向前走
            frontMonster = monster.m_frontMonsterSprite;
            if(frontMonster == null || frontMonster == undefined)
            {
                break;
            }
            frontMonsterPosition = frontMonster.getPosition();
        }

        var nextMonster = monster.m_nextMonsterSprite;
        if(nextMonster == null || nextMonster == undefined)
        {
            return;
        }
        var nextMonsterPosition = nextMonster.getPosition();

        while(nextMonsterPosition.y > position.y)
        { //下一个monster比较大
            this.exchangeMonsters(monster,nextMonster);
            nextMonster = monster.m_nextMonsterSprite;
            if(nextMonster == null || nextMonster == undefined)
            {
                break;
            }
            nextMonsterPosition = nextMonster.getPosition();
        }*/
    },
    //交换2个Monster
    exchangeMonsters : function(frontMonster,monster)
    {
        frontMonster.m_frontMonsterSprite.m_nextMonsterSprite = monster;
        if(monster.m_nextMonsterSprite != null && monster.m_nextMonsterSprite != undefined)
        {
            monster.m_nextMonsterSprite.m_frontMonsterSprite = frontMonster;
        }
        frontMonster.m_nextMonsterSprite = monster.m_nextMonsterSprite;
        monster.m_frontMonsterSprite = frontMonster.m_frontMonsterSprite;
        frontMonster.m_frontMonsterSprite = monster;
        if(monster.m_nextMonsterSprite != null && monster.m_nextMonsterSprite != undefined)
        {
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
    removeMonsterSprite : function(monster)
    {
        cc.log("remove from monster Sprite " + monster.m_weiyi);
        var frontMonster = monster.m_frontMonsterSprite;
        var nextMonster = monster.m_nextMonsterSprite;
        frontMonster.m_nextMonsterSprite = nextMonster;
        if(nextMonster != null && nextMonster != undefined)
        {
            nextMonster.m_frontMonsterSprite = frontMonster;
        }
        monster.m_nextMonsterSprite = null;
        monster.m_frontMonsterSprite = null;
    }


});