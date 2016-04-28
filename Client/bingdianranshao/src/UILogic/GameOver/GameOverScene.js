/**
 * Created by jiachen on 2016/4/21.
 */



var GameOverlayer = cc.Scene.extend({

        gameOverLayerJson : null,
        ctor : function(){
            this._super();
            this.gameOverLayerJson = ccs.load(res.GO_SettlementLayer_json).node;
            this.addChild(this.gameOverLayerJson);

            var backButton = ccui.helper.seekWidgetByName(this.gameOverLayerJson,"Back_Button");
            backButton.addClickEventListener(this.backButtonClickEvent);
            if(GC.ISWIN){
                var imageView = ccui.helper.seekWidgetByName(this.gameOverLayerJson,"win_imageview");
                imageView.setVisible(true);
            }
            else{
                var imageView = ccui.helper.seekWidgetByName(this.gameOverLayerJson,"lose_imageview");
                imageView.setVisible(true);
            }
            this.schedule(this.recvMessage,0);//计时器
        },

        backButtonClickEvent : function(){
            cc.log("send back room list message");
            GameJoy.Proxy.SendRequest(NetIdentify["MSG_BACK_ROOM"]);
        },

        recvMessage : function(){
            var id = GameJoy.Proxy.RecvResponse();
            cc.log("recv message !!!!!!!!!!!!!!!!!!!!" + id);
            if(id == NetIdentify["MSG_BACK_ROOM_LIST"]){
                cc.log("send back room list message");
                cc.director.replaceScene(new MainMenuScene());
            }
        }
    }
);

var GameOverScene = cc.Scene.extend({
    gameOverlayer : null,
    onEnter : function(){
        this._super();
        this.gameOverlayer = new GameOverlayer();
        this.addChild(this.gameOverlayer);
    }
});
