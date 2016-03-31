/**
 * Created by jiachen on 2016/3/28.
 */

var MMBackgroundLayer = cc.Layer.extend({
    _sptBg     : null,
    ctor : function(){
        this._super();
        this.initBackground();
    },

    initBackground : function(){
        var mainscene = ccs.load(res.MM_MainScene_json);
        this.addChild(mainscene.node);
    }
});