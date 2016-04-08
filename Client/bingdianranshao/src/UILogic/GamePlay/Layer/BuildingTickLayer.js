/**
 * Created by jiachen on 2016/4/7.
 */

var BuildingTicklayer = cc.Layer.extend({
    ctor : function(){
        this._super();
    },

    addTickSprite : function(position){
        var sprite = cc.Sprite.create(res.GM_PickImage_png);
        sprite.setPosition(position);
        this.addChild(sprite);
    }
});
