/**
 * Created by JiaChen on 2016/4/20.
 */

var BagTouchSprite = cc.Sprite.extend({
    m_id : null,
    m_config : null,
    m_attributePanel : null,
    ctor : function(config){
        this._super(config.attribute.defaultImage);
        this.m_id = config.attribute.id;
        this.m_config  = config;
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
        this.m_attributePanel = ccui.helper.seekWidgetByName(g_mainscene, "AttributePanel");
        this.m_attributePanel.setVisible(true);
        target.setBagPanel(target.m_config);
        return true;
    },
    onTouchMoved : function (touch, event) {
    },
    onTouchEnded : function (touch, event) {
        this.m_attributePanel.setVisible(false);
    },
    onTouchCancelled : function (touch, event) {
    },

    isTouchInRect:function (touch) {
        var getPoint = touch.getLocation();
        point = this.convertToWorldSpace(cc.p(this.width/2,this.height/2));
        myRect = cc.rect(point.x - this.width/2.0,point.y - this.height/2.0,this.width,this.height);
        return cc.rectContainsPoint(myRect, getPoint);
    },

    setBagPanel : function(config){
        var name_text = ccui.helper.seekWidgetByName(g_mainscene, "atribute_name");
        name_text.setString(config.name);
        //var HP_text = ccui.helper.seekWidgetByName(g_mainscene,   "atribute_HP");
    }
});