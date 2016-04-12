/**
 * Created by jiachen on 2016/4/11.
 */

var monsterManager;
var MonsterManager = cc.Class.extend({
    //暂时没用到
    /*myMainBuildingSprite : null,
     enemyMainBuildingSprite : null,
     myMonsterArray : null, //用来存放我方怪物，包括怪物，建筑类
     enemyMonsterArray : null,*/

    headMonsterSprite : null,

    ctor : function(){

        /*this.myMonsterArray = []; //创建一个数组
         this.enemyMonsterArray = [];*/

        this.headMonsterSprite = new MonsterSprite(MonsterConfig.yuangujuren);
        this.headMonsterSprite.setPosition(0,700);
        this.headMonsterSprite.getPosition();
        this.headMonsterSprite.m_localZOrder = 0;
        monsterManager = this;
    },

    addMonsterSprite : function (monsterSprite) {
        /*if(monsterSprite.m_id < 100){
            cc.log(111);
        }*/
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
        this.updataLocalZOrder(monsterSprite);

    },
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
    monsterChangeY : function(monster){
        var position = monster.getPosition();
        var frontMonster = monster.m_frontMonsterSprite;
        var frontMonsterPosition = frontMonster.getPosition();
        while(frontMonsterPosition.y < position.y){//上一个monstery比较小

            /*frontMonster.m_frontMonsterSprite.m_nextMonsterSprite = monster;
            monster.m_nextMonsterSprite.m_frontMonsterSprite = frontMonster;
            frontMonster.m_nextMonsterSprite = monster.m_nextMonsterSprite;
            monster.m_frontMonsterSprite = frontMonster.m_frontMonsterSprite;
            frontMonster.m_frontMonsterSprite = monster;
            monster.m_nextMonsterSprite = frontMonster;

            //交换
            var temp = frontMonster.m_localZOrder;
            frontMonster.m_localZOrder = monster.m_localZOrder;
            monster.m_localZOrder = temp;
            frontMonster.setLocalZOrder(frontMonster.m_localZOrder);
            monster.setLocalZOrder(monster.m_localZOrder);*/
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
        }
    },

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


    removeMonsterSprite : function(monster){
        //cc.log("remove from monster SPrite");
        var frontMonster = monster.m_frontMonsterSprite;
        var nextMonster = monster.m_nextMonsterSprite;
        frontMonster.m_nextMonsterSprite = nextMonster;
        if(nextMonster != null && nextMonster != undefined){
            nextMonster.m_frontMonsterSprite = frontMonster;
        }
        monster.m_nextMonsterSprite = null;
        monster.m_frontMonsterSprite = null;
    }
    /*addMonster : function(id, position, isMyMonster){
     var monsterConfig = MonsterConfig.id;
     var offset = gamePlayLayer.scrollView.getInnerContainer().getPosition(); //计算当前scrollview的偏移

     }*/


});