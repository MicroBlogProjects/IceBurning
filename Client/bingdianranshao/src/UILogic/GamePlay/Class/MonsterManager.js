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

        this.headMonsterSprite = new MonsterSprite(MonsterConfig.yuangujuren)
        monsterManager = this;
    },

    addMonsterSprite : function (monsterSprite) {
        var indexMonster = this.headMonsterSprite;
        var nextMonster  = this.headMonsterSprite.m_nextMonsterSprite;
        var position = monsterSprite.getPosition();
        while(nextMonster != null && nextMonster != undefined){
            var nextPosition = nextMonster.getPosition();
            if(nextPosition.y <= position.y ){//向下顺移
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
    },
    monsterChangeY : function(monster){
        var frontMonster = monster.m_frontMonsterSprite;
        var nextMonster = monster.m_nextMonsterSprite;

        frontMonster.m_nextMonsterSprite = nextMonster;
        if(nextMonster !=null && nextMonster !=undefined){
            nextMonster.m_frontMonsterSprite = frontMonster;
        }
        this.addMonsterSprite(monster);
    },

    removeMonsterSprite : function(monster){
        var frontMonster = monster.m_frontMonsterSprite;
        var nextMonster = monster.m_nextMonsterSprite;
        frontMonster.next.m_nextMonsterSprite = nextMonster;
        nextMonster.m_frontMonsterSprite = frontMonster;
        monster.m_nextMonsterSprite = null;
        monster.m_frontMonsterSprite = null;
    }
    /*addMonster : function(id, position, isMyMonster){
     var monsterConfig = MonsterConfig.id;
     var offset = gamePlayLayer.scrollView.getInnerContainer().getPosition(); //计算当前scrollview的偏移

     }*/


});