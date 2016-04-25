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
        this.setScale(2);
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
        //cc.log("point x is "+point.x);
        //cc.log("offset x is "+offset.x);
        var l_willPoint = monsterBackGroundLayer.TouchOfEnd(point);
        if(target.m_config.attribute.coincost > GC.CoidNum){
            return;
        }
        if(l_willPoint.point.x <=0 )
        {
            return ;
        }
        var x = l_willPoint.tiled[0].x;
        var y = l_willPoint.tiled[0].y;
        var step = new GameJoy.JS_PBFrameMessage();
        step.set_uin(GC.UIN);
        step.set_obj_id(target.m_id);
        step.set_pos_x(x);
        step.set_pos_y(y);
        step.set_type(UserOperatorType.Monster);
        var requestInstance = GameJoy.JS_CSFrameSyncRequest.Instance();
        requestInstance.set_step(step);
        GameJoy.Proxy.SendRequest(NetIdentify["MSG_FRAME_SYNC"]);
        //var position =target.GetPointOfBuild(target.m_id,cc.p(x,y));
        //monsterManager.addMonsterSprite(target.m_id,position,true);
        //cc.log("uin is "+ GC.UIN);
        //cc.log("id is "+target.m_id);
        //cc.log("x is "+x);
        //cc.log("y is "+ y);
        //cc.log("type is "+ UserOperatorType.Monster);
        //cc.log("send Monster Message id " + NetIdentify["MSG_FRAME_SYNC"]);

    },
    onTouchCancelled : function (touch, event) {
    },

    isTouchInRect:function (touch) {
        var getPoint = touch.getLocation();
        point = this.convertToWorldSpace(cc.p(this.getContentSize().width/2,this.getContentSize().height/2));
        myRect = cc.rect(point.x - this.getContentSize().width/2.0 - 30,point.y - this.getContentSize().height/2.0-30,this.getContentSize().width ,this.getContentSize().height);
        return cc.rectContainsPoint(myRect, getPoint);
    },

    GetPointOfBuild : function(uin,postion)
    {
        var l_position={};
        l_position.tiled=[];
        l_position.point = null;
        var tiled = battleLayerConfig.TiledMap.getLayer("layer7");
        if(uin > 100)
        {

            for(var i = 0; i < 3; i++)
            {
                var l_y = postion.y + i;
                var l_x = postion.x;

                l_position.tiled.push(cc.p(l_x,l_y));
            }
            if( (postion.y)%2 )
            {
                var l_x = postion.x + 1;
                var l_y = postion.y + 1;
                l_position.tiled.push(cc.p(l_x,l_y));
            }else
            {
                var l_x = postion.x - 1;
                var l_y = postion.y + 1;
                l_position.tiled.push(cc.p(l_x,l_y));
            }
            var l_msize = (tiled.getTileAt(postion)).getContentSize();
            var l_mpoint = (tiled.getTileAt(postion)).getPosition();
            l_position.point = cc.p( l_mpoint.x+32, l_mpoint.y+16);
            monsterBackGroundLayer.PushDownTower(l_position.tiled,1);

        }else
        {
            l_position.tiled.push(postion);
            l_position.point = (tiled.getTileAt( postion )).getPosition();
        }

        return l_position;
    }
});
