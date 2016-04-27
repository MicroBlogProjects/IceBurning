/**
 * Created by JiaChen on 2016/4/20.
 */

var BagTouchSprite = cc.Sprite.extend({
    m_id : null,
    m_config : null,
    m_attributePanel : null,
    m_isSelect : false,
    m_select: null,
    m_num : null,
    ctor : function(config,num){
        this._super(config.attribute.defaultImage);
        this.m_id = config.attribute.id;
        this.m_config  = config.attribute;
        this.m_num = num;
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
        var select = ccui.helper.seekWidgetByName(g_mainscene, "seleted_imageview_"+target.m_num);
        var IDlist;
        var maxAccount;
        if(target.m_id < 100){
            maxAccount = MAXMonsterAccount
            IDlist = MonsterIDList;
        }
        else {
            maxAccount = MAXBuildingAccount;
            IDlist = BuildingIDlist;
        }
        if(!target.m_isSelect){
            if(IDlist.length < maxAccount){
                target.m_isSelect = !target.m_isSelect;
                select.setVisible(target.m_isSelect);
                IDlist.push(target.m_id);
            }
        }
        else{
            target.m_isSelect = !target.m_isSelect;
            select.setVisible(target.m_isSelect);
            for(var i =0; i < IDlist.length ;i++){
                var monsterID = IDlist[i];
                if(monsterID == target.m_id){
                    IDlist.splice(i,1);
                    break;
                    //cc.log("delete ID "+monsterID);
                }
            }
        }
        /*cc.log('--------------------');
        for(var i = 0;i<IDlist.length;i++){
            cc.log("select iD is " + IDlist[i]);
        }*/
        this.m_attributePanel = ccui.helper.seekWidgetByName(g_mainscene, "AttributePanel");
        if(target.getPosition().x > 342){
            this.m_attributePanel.setPosition(170,145);
        }
        else {
            this.m_attributePanel.setPosition(550,145);
        }
        this.m_attributePanel.setVisible(true);
        var config = target.m_config;
        var name_text = ccui.helper.seekWidgetByName(g_mainscene, "atribute_name");
        var HP_text = ccui.helper.seekWidgetByName(g_mainscene, "atribute_HP");
        var attack_text = ccui.helper.seekWidgetByName(g_mainscene, "atribute_attack");
        var defense_text = ccui.helper.seekWidgetByName(g_mainscene, "atribute_defense");
        var attackSpeed_text = ccui.helper.seekWidgetByName(g_mainscene, "atribute_attack_speed");
        var walkSpeed_text = ccui.helper.seekWidgetByName(g_mainscene, "atribute_walk_speed");
        var attackRadius_text = ccui.helper.seekWidgetByName(g_mainscene, "atribute_attack_radius");
        var signRadius_text = ccui.helper.seekWidgetByName(g_mainscene, "atribute_sign_radius");
        name_text.setString(config.name);
        HP_text.setString(config.HP);
        attack_text.setString(config.attack);
        defense_text.setString(config.defense);
        attackSpeed_text.setString(config.attackSpeed);
        walkSpeed_text.setString(config.walkSpeed);
        attackRadius_text.setString(config.attackRadius);
        signRadius_text.setString(config.sightRadius);
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
    }

});