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
        var l_rooms = l_oppen.get_rooms();
        cc.log(l_rooms.length);
        var listView = ccui.helper.seekWidgetByName(g_mainscene, "m_ListView_room");
        listView.removeAllItems();
        var Panel_room = ccui.helper.seekWidgetByName(g_mainscene, "Panel_room");
        for(var i=0; i<l_rooms.length; i++)
        {
            var l_temp = Panel_room.clone();
            var l_room = l_rooms[i];
            l_temp.setVisible(true);
            var l_name_text = ccui.helper.seekWidgetByName(l_temp, "m_name");
            l_name_text.setString(l_room.get_username());
            var l_uid_text = ccui.helper.seekWidgetByName(l_temp,"m_uid");
            l_uid_text.setString(l_room.get_uin());
            var Panel_room_button = ccui.helper.seekWidgetByName(l_temp,"m_Button_start");
           if(GC.UIN != l_room.get_uin())
           {
             Panel_room_button.uindd=l_room.get_uin();
             Panel_room_button.addClickEventListener(
                 function (sender, eventType) {
                     var temp=GameJoy.JS_CSJoinRoomRequest.Instance();
                     temp.set_uin(this.uindd);
                     GameJoy.Proxy.SendRequest(5);
                 }
             );
           }
           else
           {
               Panel_room_button.setEnabled(false);
           }
           listView.pushBackCustomItem(l_temp);
        }
    },
    createMyRoom:function(id)
    {
       GC.IS_HOST = true;
       this.buttonFreshRoomTouchEvent();
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
        GameJoy.Proxy.SendRequest(4);
    },
    buttonFreshRoomTouchEvent:function()
    {
        GameJoy.Proxy.SendRequest(3);
    }
});
