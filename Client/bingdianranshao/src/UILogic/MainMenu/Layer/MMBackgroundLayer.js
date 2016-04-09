/**
 * Created by jiachen on 2016/3/28.
 */
var g_mainscene;
var g_this;
var MMBackgroundLayer = cc.Layer.extend({
    _sptBg: null,
    ctor: function () {
        this._super();
        this.initBackground();
        this.playMusic();
        g_this = this;
    },
    playMusic: function () {

//        播放背景音乐，true代表循环无限次播放，false表示只播放一次。
        if (GC.SOUND_ON) {
            if (cc.audioEngine.isMusicPlaying()) {
                return;
            }
            cc.audioEngine.playMusic(res.MM_BgMusic_mp3, true);
        }
    },
    initBackground: function () {
        g_mainscene = ccs.load(res.LI_LoginJson_json).node;
        this.addChild(g_mainscene);
        var l_loginButton = ccui.helper.seekWidgetByName(g_mainscene, "m_Button_login");
        l_loginButton.addTouchEventListener(this.buttonTouchEvent);
    },
    buttonTouchEvent: function () {


        g_this.flareEffect();
        var l_text_name = ccui.helper.seekWidgetByName(g_mainscene, "m_TextField_name");
        var l_text_pwd = ccui.helper.seekWidgetByName(g_mainscene, "m_TextField_pwd");
        var l_name = l_text_name.getString();
        var l_pwd = l_text_pwd.getString();

    },
    flareEffect : function(){
       flare = new cc.Sprite(res.MM_Flare_jpg);
        flare.stopAllActions();

//        设置flare 的渲染混合模式
        flare.setBlendFunc(cc.SRC_ALPHA, cc.ONE);
        flare.attr({
            x: -30,
            y: 297,
            visible: true,
            opacity: 0,
            rotation: -120,
            scale: 0.2
        });


//        定义动作
        var opacityAnim = cc.fadeIn(0.5, 255);
        var opacDim = cc.fadeIn(1, 0);

//        为动作加上easing效果，具体参考tests里面的示例
        var biggerEase = cc.scaleBy(0.7, 1.2, 1.2).easing(cc.easeSineOut());
        var easeMove = cc.moveBy(0.5, cc.p(640, 0)).easing(cc.easeSineOut());
        var rotateEase = cc.rotateBy(2.5, 90).easing(cc.easeExponentialOut());
        var bigger = cc.scaleTo(0.5, 1);

//        函数回调动作
        var killflare = cc.callFunc(function () {
            this.getParent().removeChild(this,true);
        }, flare);

//        按顺序执行一组动作
        var seqAction = cc.sequence(opacityAnim, biggerEase, opacDim, killflare);

//        同时执行一组动作
        var action = cc.spawn(seqAction, easeMove, rotateEase, bigger);
        flare.runAction(action);
    },
    receiveMessageLogin: function ()
    {

    }
});