/**
 * Created by jiachen on 2016/4/27.
 */


var AttackAnimateInfomationData = cc.Class.extend({
    m_id : null,
    m_frame : null,
    ctor : function(id,frame){
        this.m_id = id;
        this.m_frame = frame;
    },
    operator : function(){
        var monster = monsterManager.IdMapSprite[""+this.m_id];
        if(monster == null || monster == undefined){
            return;
        }
        monster.m_activity = false;
    }
});
var DeathInfomationData = cc.Class.extend({
    m_id : null,
    m_frame : null,
    ctor : function(id,frame){
        this.m_id == id;
        this.m_frame = frame;
    },
    operator : function(){
        var monster = monsterManager.IdMapSprite[""+this.m_id];
        if(monster == null || monster ==undefined){
            return;
        }
        monster.deathCallFunc();
    }
});


var AttackInfomationData = cc.Class.extend({
    type : null,
    attack : null,
    des_id : null,
    frame :null,
    m_Camp : null,
    position : null,
    attackRadius : null,
    ctor : function(type,attack,des_id,frame,m_Camp,attackRadius){
        this.type = type;
        this.attack = attack;
        this.des_id = des_id;
        this.frame = frame;
        this.m_Camp = m_Camp;
        this.attackRadius = attackRadius;
    },
    operator : function(){
        if(this.type == 0){
            var monster = monsterManager.IdMapSprite[""+this.des_id];
            if(monster == null || monster ==undefined){
                return;
            }
            monster.m_HP -= this.attack;
        }
        else {
            cc.log("type is" +this.type + "attack is " + this.attack + "des_id is " + this.des_id + "frame is "+ this.frame + "m_Camp is " + this.m_Camp + "attackRadius" + this.attackRadius);
            var monsters = monsterManager.getMonstersInRect(1-this.m_Camp,monsterBackGroundLayer.StaggeredCoordForPosition(this.des_id), this.attackRadius);
            for(var i = 0; i< monsters.length;i++){
                var monster = monsters[i];
                monster.m_HP -= this.attack;
            }
        }
    }
});

var StepInfomationData = cc.Class.extend({
    uin : null,
    x : null,
    y : null,
    monsterId : null,
    type : null,
    frame : null,
    ctor : function(uin,x,y,monsterId,type,frame){
        this.uin = uin;
        this.x = x;
        this.y = y = y
        this.monsterId = monsterId;
        this.type = type;
        this.frame = frame;
    }
});