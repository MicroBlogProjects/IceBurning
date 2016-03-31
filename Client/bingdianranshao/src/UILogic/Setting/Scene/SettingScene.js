/**
 * Created by jiachen on 2016/3/30.
 */


var SettingLayer = cc.Layer.extend({
    backgroudLayer :null,
    touchLayer :null,
    ctor : function(){
        this._super();
        this.addBackgroundLayer();
        this.addTouchLayer();
    },
    addBackgroundLayer : function(){
        this._backgroundLayer = new STBackgroundLayer();
        this.addChild(this._backgroundLayer);
    },
    addTouchLayer : function(){
        this._touchLayer = new STTouchLayer();
        this.addChild(this._touchLayer);
    }
});
var SettingScene = cc.Scene.extend({
    ctor :function(){
        this._super();
        var settinglayer = new SettingLayer();
        this.addChild(settinglayer);
    }
});
