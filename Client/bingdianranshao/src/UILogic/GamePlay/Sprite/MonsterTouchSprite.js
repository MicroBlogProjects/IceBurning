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
        var l_target = event.getCurrentTarget();
        if (!l_target.isTouchInRect(touch)){
            return false;
        }
        MonsterTouch.addListerSprite(l_target.m_config,touch.getLocation());
        var l_point = touch.getLocation();
        var l_offset = gamePlayLayer.scrollView.getInnerContainer().getPosition(); //计算当前scrollview的偏移
        l_point.x -= l_offset.x;
        battleLayerConfig.buildType = (l_target.m_id>100)?2:1;
        monsterBackGroundLayer.TouchOfBegin(l_point);
        return true;
    },
    onTouchMoved : function (touch, event) {
        MonsterTouch.moveListerSprite(touch.getLocation());
        var l_point = touch.getLocation();
        var l_offset = gamePlayLayer.scrollView.getInnerContainer().getPosition(); //计算当前scrollview的偏移
        l_point.x -= l_offset.x;
        monsterBackGroundLayer.TouchOfMove(l_point);
    },
    onTouchEnded : function (touch, event) {
        var target = event.getCurrentTarget();
        MonsterTouch.removeListerSprite();
        var point = touch.getLocation();
        var offset = gamePlayLayer.scrollView.getInnerContainer().getPosition(); //计算当前scrollview的偏移
        point.x -= offset.x;
        var l_willPoint = monsterBackGroundLayer.TouchOfEnd(point);
        if(l_willPoint.point.x>=0)
        {   
            monsterManager.addMonsterSprite(target.m_id, l_willPoint,true);
        }
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
