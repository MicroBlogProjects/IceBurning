/**
 * Created by jiachen on 2016/3/29.
 */

var MonsterLayer = cc.Layer.extend({
    monsterArray : null,

    ctor : function(){
        this._super();
        this.monsterArray = new Array();
    },
    addMonsterNode : function(config,direct){
        var mosterNode = new MonsterNode(config,direct);
        mosterNode.m_target.setPosition(400,200);
        this.addChild(mosterNode.m_target);
        mosterNode.walkingAnimate();
    }
});