/**
 * Created by jiachen on 2016/4/4.
 */

var MonsterTouchSprite = cc.Sprite.extend({
    m_id : null,
    ctor : function(config){
        this._super(config.defaultImage);

        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,
            onTouchBegan: this.onTouchBegan,
            onTouchMoved: this.onTouchMoved,
            onTouchEnded: this.onTouchEnded,
            onTouchCancelled : this.onTouchCancelled
        }, this);
    },
    onTouchBegan : function (touch, event) {
        var target = event.getCurrentTarget();
        if (!target.isTouchInRect(touch)){
            return false
        }
        MonsterTouch.addListerSprite(touch.getLocation());
        monsterManager.addClipperNode();
        return true;
    },
    onTouchMoved : function (touch, event) {
        //var target = event.getCurrentTarget();
        MonsterTouch.moveListerSprite(touch.getLocation());

    },
    onTouchEnded : function (touch, event) {
        //var target = event.getCurrentTarget();
        MonsterTouch.removeListerSprite();
        monsterManager.removeClipperNode();
        config = MonsterConfig.yuangujuren;
        var point = touch.getLocation();
        monsterManager.addMyMonsterSprite(config, point);

    },
    onTouchCancelled : function (touch, event) {
        var target = event.getCurrentTarget();

    },

    isTouchInRect:function (touch) {
        var getPoint = touch.getLocation();
        point = this.convertToWorldSpace(cc.p(this.width/2,this.height/2));
        myRect = cc.rect(point.x - this.width/2.0,point.y - this.height/2.0,this.width,this.height);
        return cc.rectContainsPoint(myRect, getPoint);
    }

});
