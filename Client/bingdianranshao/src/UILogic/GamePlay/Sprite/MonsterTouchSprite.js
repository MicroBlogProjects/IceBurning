/**
 * Created by jiachen on 2016/4/4.
 */

var MonsterTouchSprite = cc.Sprite.extend({
    m_id : null,
    m_config : null,
    ctor : function(config){
        this._super(config.attribute.Icon);
        this.m_config = config;
        this.m_id = config.attribute.id;
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
            return false;
        }
        MonsterTouch.addListerSprite(target.m_config,touch.getLocation());
        if(target.m_id < 100){
            monsterBackGroundLayer.addClipperNode();
        }
        else{
            monsterBackGroundLayer.addBuildingTick();
        }
        return true;
    },
    onTouchMoved : function (touch, event) {
        MonsterTouch.moveListerSprite(touch.getLocation());

    },
    onTouchEnded : function (touch, event) {
        var target = event.getCurrentTarget();
        MonsterTouch.removeListerSprite();
        var point = touch.getLocation();
        var offset = gamePlayLayer.scrollView.getInnerContainer().getPosition(); //计算当前scrollview的偏移
        point.x -= offset.x;
        cc.log("point x is "+point.x);
        cc.log("offset x is "+offset.x);

        if(target.m_id < 100){
            monsterBackGroundLayer.removeClipperNode();
        }
        else {
            monsterBackGroundLayer.removeBuildingTick();
        }
        cc.log("target id  is "+ target.m_id);
        var step = new GameJoy.JS_PBFrameMessage();
        step.set_uin(GC.UIN);
        step.set_obj_id(target.m_id);
        step.set_pos_x(parseInt(point.x));
        step.set_pos_y(parseInt(point.y));
        step.set_type(UserOperatorType.Monster);
        var requestInstance = GameJoy.JS_CSFrameSyncRequest.Instance();
        requestInstance.set_step(step);
        GameJoy.Proxy.SendRequest(NetIdentify["MSG_FRAME_SYNC"]);
        cc.log("uin is "+ GC.UIN);
        cc.log("id is "+target.m_id);
        cc.log("x is "+point.x);
        cc.log("y is "+ point.y);
        cc.log("type is "+ UserOperatorType.Monster);
        cc.log("send Monster Message id " + NetIdentify["MSG_FRAME_SYNC"]);

    },
    onTouchCancelled : function (touch, event) {
    },

    isTouchInRect:function (touch) {
        var getPoint = touch.getLocation();
        point = this.convertToWorldSpace(cc.p(this.width/2,this.height/2));
        myRect = cc.rect(point.x - this.width/2.0,point.y - this.height/2.0,this.width,this.height);
        return cc.rectContainsPoint(myRect, getPoint);
    }

});
