/**
 * Created by jiachen on 2016/3/30.
 */

var STBackgroundLayer = cc.Layer.extend({

    ctor : function(){

        this._super();

        this.initBackground();
    },

    initBackground : function(){

        var mainscene = ccs.load(res.MM_MainScene_json);
        this.addChild(mainscene.node);
    }
});