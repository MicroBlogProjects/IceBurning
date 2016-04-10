/**
 * Created by jiachen on 2016/3/28.
 */
var g_mainscene;
var g_this;
var useName;
var MMTouchLayer = cc.Layer.extend({

    ctor : function()
    {
        this._super();
        g_this = this;
        this.initUI();
    	this.schedule(this.receiveMessage,0.1);
        this.buttonFreshRoomTouchEvent();
        this.ismyRoom=false;
    },
    createRoom:function(id)
    {
        var index = ""+id;
        var l_oppen = NetConfig[index]();//GameJoy.JS_CSLoginResponse.Instance();
        var is_success = l_oppen.get_result();
        if(is_success != 0 )return ;
        var l_person = l_oppen.get_rooms();

        var Panel_room = ccui.helper.seekWidgetByName(g_mainscene, "Panel_room");
        Panel_room.setVisible(true);
        var l_name_text = ccui.helper.seekWidgetByName(g_mainscene, "m_name");
        l_name_text.setString(l_person.get_username());
        var l_uid_text = ccui.helper.seekWidgetByName(g_mainscene,"m_uid");
        l_uid_text.setString(l_person.get_uin());
        var Panel_room_button = ccui.helper.seekWidgetByName(g_mainscene,"m_Button_start");
        Panel_room_button.addClickEventListener(this.buttonJoinBattleTouchEvent);
    },
    createMyRoom:function(id)
    {
        var Panel_room = ccui.helper.seekWidgetByName(g_mainscene, "Panel_room");
        Panel_room.setVisible(true);
        var panel_text = ccui.helper.seekWidgetByName(g_mainscene, "m_name");
        panel_text.setString(g_this.parent.m_Name);
    },
    JoinBattle:function(id)
    {
        this.unschedule(this.receiveMessage());
        g_this.parent.addChosePack();
        this.removeFromParent();
    },
    receiveMessage:function()
    {
        var id = GameJoy.Proxy.RecvResponse();
        if(id > 0)
        {
            if(id == 3)
            {
                cc.log("------------------------sheng qin lie biao-------------------");
                this.createRoom(id);
            }
            if(id == 4)
            {
                this.createMyRoom(id);
            }
            if(id == 5)
            {
                this.JoinBattle(id);
            }
        }
    },
    initUI:function()
    {
        g_mainscene = ccs.load(res.MT_MainView_json).node;
        this.addChild(g_mainscene);
        var create_room = ccui.helper.seekWidgetByName(g_mainscene, "m_button_create");
        create_room.addClickEventListener(this.buttonCreateRoomTouchEvent);
        var refresh_room = ccui.helper.seekWidgetByName(g_mainscene,"m_refresh");
        refresh_room.addClickEventListener(this.buttonFreshRoomTouchEvent);
    },
    buttonCreateRoomTouchEvent:function()
    {
        cc.log("4----------------------------creatRoom");
        GameJoy.Proxy.SendRequest(4);
    },
    buttonJoinBattleTouchEvent:function()
    {
        cc.log("5----------------------------JoinRoom");
        GameJoy.Proxy.SendRequest(5);
    },
    buttonFreshRoomTouchEvent:function()
    {
        cc.log("3----------------------------PullRoomList");
        GameJoy.Proxy.SendRequest(3);
    }
});
