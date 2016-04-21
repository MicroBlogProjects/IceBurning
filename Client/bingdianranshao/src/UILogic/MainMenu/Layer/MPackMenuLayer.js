/**
 * Created by opas on 2016/4/10.
 */
var g_mainscene;
var g_this;
var MPackMenuLayer = cc.Scene.extend({
    ctor : function()
    {
    this._super();
    g_this = this;
    this.init();
    this.schedule(this.receiveMessage,0.1);
    },
    startBattle:function(id)
    {
        var index = ""+id;
        var fight_res = NetConfig[index]();//GameJoy.JS_CSLoginResponse.Instance();
        if(fight_res.get_result() !=0 )
            return ;
        this.unschedule(this.receiveMessage());
        g_this.parent.addBattleLayer();
        this.removeFromParent();
    },
    receiveMessage:function()
    {
        var id = GameJoy.Proxy.RecvResponse();
        if(id > 0)
        {
            if(id == 6)
            {
               this.startBattle(id);
            }
        }
    },
    init:function(){
        g_mainscene = ccs.load(res.PB_MainView_json).node;
        this.addChild(g_mainscene);
        var l_startButton = ccui.helper.seekWidgetByName(g_mainscene, "m_Button_start");
        l_startButton.addClickEventListener(this.buttonStartTouchEvent);
        this.setIcon();
    },
    buttonStartTouchEvent:function()
    {
        GameJoy.Proxy.SendRequest(6);
    },

    setIcon: function(){
        var panel = ccui.helper.seekWidgetByName(g_mainscene,"BagPanel");
        var height = panel.height;
        var width = panel.width;
        var account = 0;
        for(var value in MonsterConfig){
            var config = MonsterConfig[value];
            var x = (0.14 + (account % 5)*0.18)*width;
            var y = (0.80 - parseInt(account /5)*0.3) * height;
            ++ account;
            var sprite = new BagTouchSprite(config,account);
            sprite.setPosition(x,y);
            panel.addChild(sprite);
        }
    }
});