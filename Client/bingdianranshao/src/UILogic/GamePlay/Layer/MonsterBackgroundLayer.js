/**
 * Created by jiachen on 2016/3/29.
 */
//弃用
//管理所有的怪物
var ScheduleTime =1.0/10;
var TestTime = 2;
var monsterBackGroundLayer;
var MonsterBackgroundLayer = cc.Layer.extend({
    m_clipperNode : null,
    buildingTickLayer : null,

    TMXTiledMap :null,

    ctor : function()
    {
        this._super();
        this.TMXTiledMap = new cc.TMXTiledMap(res.GM_Map_tmx);
        this.addChild(this.TMXTiledMap,0);
        var l_layer4 = this.TMXTiledMap.getLayer("layer4");
        l_layer4.setVisible(true);
        for(var i = 0; i<battleLayerConfig.width; i++)
            for(var j = 0; j<battleLayerConfig.height; j++)
            {
                var l_block = l_layer4.getTileAt(cc.p(i,j));
                if(l_block !=null)
                {
                    var l_id = i*battleLayerConfig.height + j;
                    battleLayerConfig.iscanPutDown[l_id]=1;
                    battleLayerConfig.canPutDown.push(l_id);
                    l_block.setVisible(false);
                    var l_siz=l_block.getContentSize();
                    var l_pos = l_block.getPosition();
                    var rect=cc.rect(l_pos ,l_siz);
                    battleLayerConfig.canPutDownRect.push(rect);
                }
            }
        monsterBackGroundLayer = this;
    },
    myRectContainsPoint:function(point)
    {
        var l_layer4 = this.TMXTiledMap.getLayer("layer4");
        for(var i = 0;  i < battleLayerConfig.highlight.length; ++i)
        {
            var block = battleLayerConfig.highlight[i];
            if(block == null)continue;
            block.setVisible(false);
        }
        var l_numofblock = 0;
        for(var i = 0; i < battleLayerConfig.canPutDown.length; i++)
        {
            if( cc.rectContainsPoint(battleLayerConfig.canPutDownRect[i],point) )
            {
                var id = battleLayerConfig.canPutDown[ i ];
                var x = id / battleLayerConfig.height;
                x=Math.floor(x);
                var y = id % battleLayerConfig.height;
                var tx=x;
                for(var j = 0; j<3; j++)
                {
                    var ty = y + j;
                    var id = tx*battleLayerConfig.height+ty;
                    if(battleLayerConfig.iscanPutDown[id]!=1)
                        continue;
                    ++ l_numofblock;
                    var block = l_layer4.getTileAt(cc.p(tx, ty));
                    block.setVisible(true);
                    battleLayerConfig.highlight[j]=block;
                }
                if(y%2 == 1)
                {
                    tx = x+1;
                    var ty = y + 1;
                    var id = tx*battleLayerConfig.height+ty;
                    if(battleLayerConfig.iscanPutDown[id]==1)
                    {
                        var block = l_layer4.getTileAt(cc.p(tx, ty));
                        block.setVisible(true);
                        ++l_numofblock;
                        battleLayerConfig.highlight[j] = block;
                    }
                }else
                {
                       tx=x-1;
                        var ty = y + 1;
                        var id = tx*battleLayerConfig.height+ty;
                        if(battleLayerConfig.iscanPutDown[id]==1)
                        {
                            var block = l_layer4.getTileAt(cc.p(tx, ty));
                             block.setVisible(true);
                            ++l_numofblock;
                            battleLayerConfig.highlight[j]=block;
                        }
                }
                break;
            }
        }
        return l_numofblock == 4;
    },
    //拖动怪物的效果
    addClipperNode :function(){
        //设置模板
        /*var stencil = checkPathManager.getStencil();
        //设置
        this.m_clipperNode = cc.ClippingNode.create(stencil);
        this.m_clipperNode.setInverted(true);//底板可见
        this.m_clipperNode.setAlphaThreshold(1.0);
        //设置灰色的底板
        var baLayer = cc.LayerColor.create(cc.color(0,0,0,150));
        baLayer.setScaleX(4);
        this.m_clipperNode.addChild(baLayer);
        this.addChild(this.m_clipperNode,0);*/
    },
    removeClipperNode : function(){
        /*this.m_clipperNode.removeFromParent();
        this.m_clipperNode = null;*/
    },

    //技能效果
    skillAnimate :function(skillConfig,elemy){
        var skillSprite = new SkillSprite(skillConfig);
        skillSprite.setPosition(elemy.getPosition().x,elemy.getPosition().y -60 );
        skillSprite.attackAnimate(elemy);
        this.addChild(skillSprite);
    },

    //拖动建筑物效果
    addBuildingTick : function(){
        /*this.buildingTickLayer = new BuildingTicklayer();
        this.addChild(this.buildingTickLayer,LAYER_PRIORITY_TOUCH-1);
        var positions = checkPathManager.getBuildintPositions();
        for(var i = 0; i < positions.length; i++){
            var position = positions[i];
            this.buildingTickLayer.addTickSprite(position);
        }*/
    },
    removeBuildingTick : function(){
        //this.buildingTickLayer.removeFromParent();
        //this.buildingTickLayer = null;
    }


});
