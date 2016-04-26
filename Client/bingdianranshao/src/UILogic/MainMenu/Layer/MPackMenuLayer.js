/**
 * Created by opas on 2016/4/10.
 */
var g_mainscene;
var g_this;
var MPackMenuLayer = cc.Scene.extend({
    loadingLayer : null,
    monsterPanel : null,
    buildingPanel : null,
    buttonStates : 0,
    ctor : function()
    {
    this._super();
    g_this = this;
    this.init();
    //this.schedule(this.receiveMessage,0.1);
    },
    startBattle:function(id)
    {
        var index = ""+id;
        var fight_res = NetConfig[index]();//GameJoy.JS_CSLoginResponse.Instance();
        if(fight_res.get_result() !=0 )
            return ;
        this.unschedule(this.receiveMessage);
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
        var monsterButton = ccui.helper.seekWidgetByName(g_mainscene, "MonsterButton");
        monsterButton.addClickEventListener(this.monsterButtonListen);
        var buildingButton = ccui.helper.seekWidgetByName(g_mainscene, "BuildingButton");
        buildingButton.addClickEventListener(this.buildingButtongListen);
        this.setIcon();
    },
    buttonStartTouchEvent:function()
    {
        this.loadingLayer = new Loadinglayer();
        this.setPosition(0,0);
        this.addChild(this.loadingLayer);
        GameJoy.Proxy.SendRequest(6);
    },

    setIcon: function(){
        this.monsterPanel = ccui.helper.seekWidgetByName(g_mainscene,"MonsterPanel");
        this.buildingPanel = ccui.helper.seekWidgetByName(g_mainscene,"BuildingPanel");
        var height = this.monsterPanel.height;
        var width = this.monsterPanel.width;
        var monsterAccount = 0;
        var buildingAccount = 0;
        for(var value in MonsterConfig){
            var config = MonsterConfig[value];
            if(value < 100){
                var x = (0.14 + (monsterAccount % 5)*0.18)*width;
                var y = (0.80 - parseInt(monsterAccount /5)*0.3) * height;
                var sprite = cc.Sprite.create(config.attribute.defaultImage);
                sprite.setPosition(x,y);
                this.monsterPanel.addChild(sprite);

                var imageView = ccui.helper.seekWidgetByName(g_mainscene,"monster_image_view"+monsterAccount);
                cc.log("imageview is "+imageView);
                imageView.setTag(value);
                imageView.setUserData(monsterAccount);
                imageView.addTouchEventListener(this.imageViewListenr,this);
                monsterAccount++;
            }
            else if(value <200){
                var x = (0.14 + (buildingAccount % 5)*0.18)*width;
                var y = (0.80 - parseInt(buildingAccount /5)*0.3) * height;
                var sprite = cc.Sprite.create(config.attribute.defaultImage);
                sprite.setPosition(x,y);
                this.buildingPanel.addChild(sprite);

                var imageView = ccui.helper.seekWidgetByName(g_mainscene,"Building_image_view"+buildingAccount);
                cc.log("imageview is "+imageView);
                imageView.setTag(value);
                imageView.setUserData(buildingAccount);
                imageView.addTouchEventListener(this.imageViewListenr,this);
                buildingAccount++;
            }
            this.buildingPanel.setVisible(false);

        }

    },

    monsterButtonListen : function(){
        g_this.buttonStates = 0;
        g_this.buildingPanel.setVisible(false);
        g_this.monsterPanel.setVisible(true);
    },

    buildingButtongListen : function(){
        g_this.buttonStates = 1;
        g_this.buildingPanel.setVisible(true);
        g_this.monsterPanel.setVisible(false);
    },

    imageViewListenr : function(sender,type){
        cc.log("serder is "+sender.getUserData());
        cc.log("type is "+ type);
        var tag = sender.getTag();
        config = MonsterConfig[""+tag].attribute;
        var userData = sender.getUserData()+1;
        var selectname;
        if(g_this.buttonStates == 0){
            selectname = "seleted_imageview_"
        }
        else{
            selectname = "seleted_imageview_b"
        }
        if(type == 0){ //0是开始
            var select = ccui.helper.seekWidgetByName(g_mainscene,selectname+userData);
            var visible = !select.isVisible();
            select.setVisible(visible);
            if(visible){
            }
        }
        else if(type == 2){
        }
    }
});