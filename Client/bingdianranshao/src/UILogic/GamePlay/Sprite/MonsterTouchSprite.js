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
        //MonsterTouch.addClipperNode();
        return true;
    },
    onTouchMoved : function (touch, event) {
        //var target = event.getCurrentTarget();
        MonsterTouch.moveListerSprite(touch.getLocation());

    },
    onTouchEnded : function (touch, event) {
        //var target = event.getCurrentTarget();
        MonsterTouch.removeListerSprite();
        //MonsterTouch.removeClipperNode();
        config = MonsterConfig.yuangujuren;
        var point = touch.getLocation();
        var type ;
        if(point.x <= GC.w_2)
        {
            type =true;
        }
        else{
            type = false;
        }
        monsterManager.addMonsterSprite(config, point,type);

    },
    onTouchCancelled : function (touch, event) {
        var target = event.getCurrentTarget();

    },

    isTouchInRect:function (touch) {
        var getPoint = touch.getLocation();
        var myRect = this.getFrame();
        myRect.x += this.x;
        myRect.y += this.y;
        return cc.rectContainsPoint(myRect, getPoint);
    },
    getFrame:function () {
        return cc.rect(-this.width / 2, -this.height / 2, this.width, this.height);
    }

});
