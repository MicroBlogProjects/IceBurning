/**
 * Created by jiachen on 2016/4/11.
 */

var monsterManager;

var MonsterManager = cc.Class.extend({

    //用户添加Monster模块
    myMainBuildingSprite : null,
    enemyMainBuildingSprite : null,
    MonsterArray : null, //用来存放我方怪物，包括怪物，建筑类
    //层级管理模块
    headMonsterSprite : null,
    IdMapSprite:null,
    times:null,
    idx1:null,
    idx2:null,
    numOfSprite:0,
    ctor : function(){
        this.numOfSprite =0;
        this.idx1 = this.idx2 = 0;
        //用户添加Monster模块
        this.MonsterArray={};
        this.IdMapSprite={};
        this.MonsterArray[0]=[];
        this.MonsterArray[1]=[];
        //层级管理模块
        this.headMonsterSprite = new MonsterSprite(MonsterConfig[""+2]);
        this.headMonsterSprite.setPosition(0,7000);
        this.headMonsterSprite.getPosition();
        this.headMonsterSprite.m_localZOrder = 0;
        this.times = 0;
        monsterManager = this;
    },

    getTime : function(){
        var mydate = new Date();
        //cc.log("minues :"+mydate.getMinutes() +"seconds"+ mydate.getSeconds()+ "millise"+mydate.getMilliseconds());
    },

    //用户添加Monster模块
    addMonsterSprite : function(id, point, isMyMonster)
    {
        var config = MonsterConfig[""+id];
        var mosterSprite;
        mosterSprite = new MonsterSprite(config,isMyMonster);
        mosterSprite.setMyPosition(point);
        monsterLayer.addMonsterSprite(mosterSprite);
        mosterSprite.m_spriteID = this.numOfSprite++;
        this.IdMapSprite[ mosterSprite.m_spriteID ] = mosterSprite;
        if(GC.IS_HOST)
        {
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
        }else
        {
            if(isMyMonster)
            {
                mosterSprite.m_Camp = 1;
                this.MonsterArray[1].push(mosterSprite);
            }
            else 
            {

                mosterSprite.m_Camp = 0;
                this.MonsterArray[0].push(mosterSprite);
            }
        }
        this.addHierarchyMonsterSprite(mosterSprite);
        if(id > 100) 
        { 
            algorithmOfStatus.PushDownTower(mosterSprite.m_TiledPosition,1);
        }
        algorithmOfStatus.AddMonster(mosterSprite,1);
     },
    //更新Monster
    updateMonsterData : function(){
        this.times=(this.times+1)%1;
        if(this.times != 0)
            return ;
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
        var len1 = this.MonsterArray[0].length;
    
        for(var i = 0;i < Math.min(len1,3); i++)
        {   
            this.idx1=(this.idx1+1)%len1;
            var  myMonster = this.MonsterArray[0][this.idx1];
            this.walk(myMonster);

        }
        var len2 = this.MonsterArray[1].length;
        
        for(var i = 0;i < Math.min(len2,3); i++)
        {      
            this.idx2=(this.idx2+1)%len2;
            var  myMonster = this.MonsterArray[1][this.idx2];
            this.walk(myMonster);
        }
    },

    walk : function(monster)
    {
        if(monster.m_id>200){
            if(monster.m_HP <=0){
                var step = new GameJoy.JS_PBFrameMessage();
                step.set_uin(GC.UIN);
                if(monster.m_isMyMonster){
                    step.set_obj_id(0);
                }
                else {
                    step.set_obj_id(1);
                }
                step.set_pos_x(0);
                step.set_pos_y(0);
                step.set_type(UserOperatorType.Settlement);
                var requestInstance = GameJoy.JS_CSFrameSyncRequest.Instance();
                requestInstance.set_step(step);
                GameJoy.Proxy.SendRequest(NetIdentify["MSG_FRAME_SYNC"]);
            }
            return ;
        }
        if(monster.m_HP <= 0)
        {
            monster.m_nextState = MonsterState.Death;
            monster.monsterAction();
            return;
        }
        algorithmOfStatus.GetStatus(monster);
        monster.monsterAction();
    },

    getPointDistance : function (p1, p2) 
    {
        return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
    },

    //用来计算范围伤害
    getMonstersInRect : function(camp,pos, radius){
        cc.log("HHHHH");
       var H = radius;
       var W = radius;
       var monsters = [];
       var l_W = radius;
       var l_H = radius;
       var l_nex = pos;
       for(var i = 0; i<H; i++)
       {
          pos = algorithmOfStatus.TurnUP(pos);
       }
       for(var i = 0; i<W; i++)
       {
          pos = algorithmOfStatus.TurnLeft(pos);
       }

       for(var i = 0; i <= W*2; i++)
       {   
          l_nex = pos;
          var l_h = l_H;
          for(var j = 0; j <= 2*H; ++j)
          {
             if((l_nex.x >= battleLayerConfig.width || l_nex.x < 0 || l_nex.y < 0 || l_nex.y >= battleLayerConfig.height)==false)   
             {
                  if((Math.abs(l_W) + Math.abs(l_h) <= l_H))
                      {
                          for( var e = 0; e < algorithmOfStatus.mapstatus[camp][l_nex.x][l_nex.y].length; ++e)
                          {
                             var id = algorithmOfStatus.mapstatus[camp][l_nex.x][l_nex.y][e];
                             monsters.push( this.IdMapSprite[ id  ]  )
                          }
                      }
             }
             l_nex=algorithmOfStatus.TurnDown(l_nex);
             l_h --;
          }
         pos=algorithmOfStatus.TurnRight(pos);
         l_W --;
       }
        return monsters;
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
        algorithmOfStatus.AddMonster(monster,-1);
        if(monster.m_id>100)
        {
            algorithmOfStatus.PushDownTower(monster.m_TiledPosition,-1);
            monsterBackGroundLayer.PushDownTower(monster.m_TiledPosition,-1);
        }
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