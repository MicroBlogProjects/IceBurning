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

    getTime : function(){
        var mydate = new Date();
        cc.log("minues :"+mydate.getMinutes() +"seconds"+ mydate.getSeconds()+ "millise"+mydate.getMilliseconds());
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
                this.addHierarchyMonsterSprite(mosterSprite);
        }
     },
    //更新Monster
    updateMonsterData : function(){
        this.updateMonsterArray();
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
        this.updataLocalZOrder(this.headMonsterSprite.m_nextMonsterSprite);
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
    },
    //交换2个Monster
    exchangeMonsters : function(frontMonster,monster){

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
    removeMonsterSprite : function(monster){
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