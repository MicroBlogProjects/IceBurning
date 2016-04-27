/**
 * Created by opas on 2016/4/10.
 */
var g_mainscene;
var g_this;
var MPackMenuLayer = cc.Scene.extend({
    loadingLayer : null,
    monsterPanel : null,
    buildingPanel : null,
    monsterInfoLayer : null,
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
        this.addChild(this.loadingLayer,150);
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
        var tag = sender.getTag();
        config = MonsterConfig[""+tag].attribute;
        var userData = sender.getUserData()+1;
        var selectname;
        var monsters;
        var maxAccount;
        if(g_this.buttonStates == 0){
            monsters = MonsterIDList;
            maxAccount = MAXMonsterAccount;
            selectname = "seleted_imageview_"
        }
        else{
            selectname = "seleted_imageview_b"
            monsters = BuildingIDlist;
            maxAccount = MAXBuildingAccount;
        }
        if(type == 0){ //0是开始
            var select = ccui.helper.seekWidgetByName(g_mainscene,selectname+userData);
            var visible = !select.isVisible();
            if(visible){
                this.monsterInfoLayer = ccs.load(res.MM_MonsterInfo_json).node;
                this.monsterInfoLayer.setPosition(28.62+51,72.86);
                this.addChild(this.monsterInfoLayer);
                var name_text = ccui.helper.seekWidgetByName(this.monsterInfoLayer,"name_text");
                name_text.setString(config.name);
                var HP_text = ccui.helper.seekWidgetByName(this.monsterInfoLayer,"HP_text");
                HP_text.setString(config.HP);
                var defense_text = ccui.helper.seekWidgetByName(this.monsterInfoLayer,"defense_text");
                defense_text.setString(config.defense);
                var attack_text = ccui.helper.seekWidgetByName(this.monsterInfoLayer,"attack_text");
                attack_text.setString(config.attack);
                var attackRadius_text = ccui.helper.seekWidgetByName(this.monsterInfoLayer,"attackRadius_text");
                attackRadius_text.setString(config.attackRadius);
                var attackSpeed_text = ccui.helper.seekWidgetByName(this.monsterInfoLayer,"attackSpeed_text");
                attackSpeed_text.setString(config.attackSpeed);
                var coincost_text = ccui.helper.seekWidgetByName(this.monsterInfoLayer,"coincost_text");
                coincost_text.setString(config.coincost);
                var walkingSpeed_text = ccui.helper.seekWidgetByName(this.monsterInfoLayer,"walkingSpeed_text");
                walkingSpeed_text.setString(config.walkSpeed);
                var monster_descrip_text = ccui.helper.seekWidgetByName(this.monsterInfoLayer,"monster_descrip_text");
                var button_chose = ccui.helper.seekWidgetByName(this.monsterInfoLayer,"m_Button_chose");
                cc.log("monsters length si "+monsters.length);
                if(monsters.length >= maxAccount){
                    button_chose.setVisible(false);
                }
                button_chose.addTouchEventListener(function(sender, type){
                    if(type == 0){
                        var IDlist;
                        if(tag < 100){
                            IDlist = MonsterIDList;
                        }
                        else{
                            IDlist = BuildingIDlist;
                        }
                        var mark = false;
                        for(var i = 0; i < IDlist.length;i++){
                            if(IDlist[i] == tag){
                                mark = true;
                            }
                        }
                        if(mark == false){
                            IDlist.push(tag);
                            cc.log("idlist length is "+IDlist.length)
                        }
                        select.setVisible(visible);
                        this.monsterInfoLayer.removeFromParent();
                    }
                },this);

                var button_cancel = ccui.helper.seekWidgetByName(this.monsterInfoLayer,"m_Button_cancel");
                button_cancel.addTouchEventListener(function(sender,type){
                    if(type == 0){
                        this.monsterInfoLayer.removeFromParent();
                    }
                },this);
            }
            else {
                var IDlist;
                if(tag < 100){
                    IDlist = MonsterIDList;
                }
                else{
                    IDlist = BuildingIDlist;
                }
                for(var i = 0; i < IDlist.length ;i++){
                    if(tag == IDlist[i]){
                        IDlist = IDlist.splice(i,1);
                        break;
                    }

                }
                select.setVisible(visible);
            }

        }
        else if(type == 2){
        }
    }
});