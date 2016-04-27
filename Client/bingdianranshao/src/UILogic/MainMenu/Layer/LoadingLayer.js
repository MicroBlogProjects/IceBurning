/**
 * Created by jiachen on 2016/4/26.
 */

var Loadinglayer = cc.Layer.extend({
    bgJson : null,
    loadSprite : null,
    ctor : function(){
        this._super();
        this.bgJson = ccs.load(res.MM_Loading_json).node;
        this.addChild(this.bgJson);
        this.loadingAnimate();
        this.schedule(this.receiveMessage,0);
    },
    loadingAnimate : function(){
        this.loadSprite = cc.Sprite.create(res.MM_LoadingDefault_png);
        this.loadSprite.setPosition(this.width/2,this.height/2);
        this.addChild(this.loadSprite);
        cc.spriteFrameCache.addSpriteFrames(res.MM_LoadingAnimate_plist);
        var animFrames = [];
        for(var i = 0; i < 8 ;i++){
            var frame = cc.spriteFrameCache.getSpriteFrame("LoadingAnimate"+i+".png");
            cc.log("frame is "+frame);
            animFrames.push(frame);
        };
        var animation = new cc.Animation(animFrames, 0.1);
        var animate = new cc.Animate(animation);
        this.loadSprite.runAction(cc.repeatForever(animate));
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
    startBattle:function(id)
    {
        var index = ""+id;
        var fight_res = NetConfig[index]();//GameJoy.JS_CSLoginResponse.Instance();
        if(fight_res.get_result() !=0 )
            return ;
        cc.director.runScene(new GamePlayScene());
    }
});
