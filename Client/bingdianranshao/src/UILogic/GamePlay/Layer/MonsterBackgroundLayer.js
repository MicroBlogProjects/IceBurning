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
        this.InitMyMap();
        monsterBackGroundLayer = this;
    },
   InitMyMap:function()
   {
       battleLayerConfig.endPoint.push(cc.p(29,17));
       battleLayerConfig.endPoint.push(cc.p(0,17));
       this.TMXTiledMap = new cc.TMXTiledMap(res.GM_Map_tmx);
       battleLayerConfig.TiledMap = this.TMXTiledMap;
       this.addChild(this.TMXTiledMap,0);
       var l_layer7 = this.TMXTiledMap.getLayer("layer7");
       l_layer7.setVisible(false);
       var l_layer4 = this.TMXTiledMap.getLayer("layer4");
       l_layer4.setVisible(true);
       var l_layer5 = this.TMXTiledMap.getLayer("layer5");
       l_layer5.setVisible(true);
       var l_st;
       var l_ed;
       for(var i = 0; i < battleLayerConfig.width; ++ i)
        for(var j = 0; j < battleLayerConfig.height; ++ j)
        {
          var l_block = l_layer4.getTileAt( cc.p( i, j ) );
          if(l_block != null)
          {
             l_block.setVisible(false);
          }
          l_block = l_layer5.getTileAt(cc.p(i, j));
          if(l_block != null)
          {
             l_block.setVisible(false);
          }
        }
       if(GC.IS_HOST)
       {
           l_st = 0; l_ed = battleLayerConfig.colums;
       }
       else
       {
           l_st = battleLayerConfig.colums;
           l_ed = battleLayerConfig.width;
       }
       //获取建筑物可放的位置
       var l_num = 0;
       for (var i = l_st; i < l_ed; ++ i)
           for (var j = 0; j < battleLayerConfig.height; ++ j)
           {
               var l_block = l_layer4.getTileAt( cc.p( i, j ) );
               if (l_block != null)
               {
                   var l_id = i * battleLayerConfig.height + j;
                   battleLayerConfig.occupiedOfblock[l_id]=0;
                   battleLayerConfig.towerLocal[l_id] = ++l_num;
                   battleLayerConfig.towerCanPutDown.push(l_id);
                   l_block.setVisible(false);                  
                   battleLayerConfig.towerCanPutDownBlock.push(l_block); 
               }
           }
       l_num = 0;
       for(var i = l_st; i < l_ed; ++ i)
       {
           for (var j = 0; j < battleLayerConfig.height; ++j)
           {
               var l_block = l_layer5.getTileAt(cc.p(i, j));
               if (l_block != null)
               {
                   var l_numOfpart  = (j<=12)?1:( j<=21?2:3);         
                   l_block.setVisible(false);
                   var l_id = i * battleLayerConfig.height + j;
                   battleLayerConfig.soldierLocal[l_id] = ++ l_num;
                   battleLayerConfig.soldierOfPart[l_id] = l_numOfpart;
                   battleLayerConfig.soldierCanPutDown.push(l_id);
                   battleLayerConfig.soldierCanPutDownBlock.push(l_block);
               }
           }
       }
       l_num = 0;
       var l_layer2 = this.TMXTiledMap.getLayer("layer2");
       for(var i = 0; i < battleLayerConfig.width; ++ i)
       {
           for(var j = 0; j < battleLayerConfig.height; ++j)
           {
              var l_block = l_layer2.getTileAt(cc.p(i,j));
              if(l_block != null)
              {
                var l_id = i * battleLayerConfig.height + j;
                battleLayerConfig.roadLocal[l_id] = ++l_num;
                battleLayerConfig.roadCanPutDown.push(l_id);
                battleLayerConfig.roadCanPutDownBlock.push(l_block);
              }
           }
       }
       var l_num=[0,0,0,0];
       for(var i = 0; i < battleLayerConfig.soldierCanPutDown.length; ++ i)
       {
        var l_id = battleLayerConfig.soldierCanPutDown[i];
        var l_part = battleLayerConfig.soldierOfPart[l_id];
        if(battleLayerConfig.roadLocal[l_id] >0 )
        {
          ++l_num[l_part];
          if(l_num[ l_part ] == 2)
          {
             var point  = battleLayerConfig.soldierCanPutDownBlock[i].getPosition();
            battleLayerConfig.soldierStartPositon[l_part] = point;
            battleLayerConfig.soldierStartID[l_part] = l_id;
          }
        }
      }
   },
   TouchOfBegin:function(point)
   {
       if(battleLayerConfig.buildType == 1)
       {
         this.WillAddSoldierOfMap(point);
       }
   },
   TouchOfMove:function(point)
   {
       if(battleLayerConfig.buildType == 2)
       {
         this.WillAddTowerOfMap(point);
       }
   },
   TouchOfEnd:function(point)
   {
       if(battleLayerConfig.buildType == 1)
       {
        return this.EndWillAddSoldierOfMap(point);
       }
       if(battleLayerConfig.buildType == 2)
       {
        return this.EndWillAddTowerOfMap(point);
       }
   }
   ,
   EndWillAddSoldierOfMap:function(point)
   {
    var l_layer5 = this.TMXTiledMap.getLayer("layer5");
    var l_part = -1;
    for(var i = 0; i < battleLayerConfig.soldierCanPutDown.length; ++ i)
    {
      var l_block = battleLayerConfig.soldierCanPutDownBlock[i];
      l_block.setVisible(false);   
      var l_rect = cc.rect(l_block.getPosition(),l_block.getContentSize());
      if(cc.rectContainsPoint(l_rect,point))
      {
        var l_id = battleLayerConfig.soldierCanPutDown[i];
        l_part = battleLayerConfig.soldierOfPart[l_id];
      }
    }
    var l_point={};
    l_point.point = cc.p(-1, -1);
    if(l_part != -1)
    {
      var l_block = battleLayerConfig.soldierCanPutDownBlock[0];
      var l_mpoint = battleLayerConfig.soldierStartPositon[l_part];
      var l_msize = l_block.getContentSize();
      l_point.point = cc.p( l_mpoint.x+l_msize.width/2, l_mpoint.y +l_msize.height/3 );
      l_point.tiled=[];
      var l_id = battleLayerConfig.soldierStartID[l_part];
      var l_x = Math.floor(l_id/battleLayerConfig.height);
      var l_y = l_id % battleLayerConfig.height; 
      l_point.tiled.push(cc.p(l_x, l_y));
    }
    return l_point;
  },
  WillAddSoldierOfMap:function(point)
  {
    var l_layer5 = this.TMXTiledMap.getLayer("layer5");
    for(var i = 0; i < battleLayerConfig.soldierCanPutDown.length; ++ i)
    {
      var l_block = battleLayerConfig.soldierCanPutDownBlock[i];
      l_block.setVisible(true)
    } 
  }
  ,
  EndWillAddTowerOfMap:function(point)
  {
    var l_numofblock = 0;
    for(var i = 0;  i < 4; ++i)
    {
      var l_block = battleLayerConfig.highLight[i];
      if(l_block == null || battleLayerConfig.highLightID[i] == -1) 
      {
        battleLayerConfig.highLight[i] = null;
        battleLayerConfig.highLightID[i] = -1;
        continue;
      }
      ++ l_numofblock;
      l_block.setVisible(false);
    } 
    var l_poin={};
    l_poin.point = cc.p(-1,-1);
    l_poin.tiled = [];
    if(l_numofblock == 4)
    {
      var l_block = battleLayerConfig.highLight[0];
      var l_mpoint = l_block.getPosition();
      var l_msize = l_block.getContentSize();
      l_poin.point = cc.p( l_mpoint.x+l_msize.width/2, l_mpoint.y +l_msize.height/2 );
      for(var i = 0; i < 4; ++i)
      {
        var l_id = battleLayerConfig.highLightID[i];
        battleLayerConfig.occupiedOfblock[l_id] = 1;
        var l_x = Math.floor(l_id/battleLayerConfig.height);
        var l_y = l_id % battleLayerConfig.height;
        l_poin.tiled.push(cc.p(l_x,l_y));
        battleLayerConfig.highLightID[i] = -1;
        battleLayerConfig.highLight[i] = null;
      }  
    }else
    {
      for(var i = 0; i < 4; ++ i)
      {
        battleLayerConfig.highLight[i] = null;
        battleLayerConfig.highLightID[i] = -1;
      }
    }
    return l_poin;
  },
  WillAddTowerOfMap:function(point)
  {
    var l_pointOfTouch = this.StaggeredCoordForPosition(point);

    var l_layer4 = this.TMXTiledMap.getLayer("layer4");
    for(var i = 0;  i < 4; ++i)
    {
      var l_block = battleLayerConfig.highLight[i];
      battleLayerConfig.highLightID[i] = -1;
      if(l_block == null) continue;
      l_block.setVisible(false);
      battleLayerConfig.highLight[i] = null;
    }
    var l_id = l_pointOfTouch.x * battleLayerConfig.height + l_pointOfTouch.y;
    var l_numofblock = 0;
    if(battleLayerConfig.towerLocal[l_id] > 0)
    {
      var l_x = l_pointOfTouch.x;
      var l_y = l_pointOfTouch.y;
      var l_tx = l_x;
      for(var j = 0; j<3; j++)
      {
        var l_ty = l_y + j;
        var l_id = l_tx * battleLayerConfig.height + l_ty;
        if( battleLayerConfig.towerLocal[l_id] == null || battleLayerConfig.towerLocal[l_id] < 1)
          continue;      
        var l_block = l_layer4.getTileAt(cc.p(l_tx, l_ty));
        battleLayerConfig.highLight[ l_numofblock ] = l_block;
        battleLayerConfig.highLightID[ l_numofblock ] = l_id;
        ++l_numofblock;
      }
      if(l_y % 2 == 1)
      {
        l_tx = l_x + 1;
        var l_ty = l_y + 1;
        var l_id = l_tx * battleLayerConfig.height + l_ty;
        if( battleLayerConfig.towerLocal[l_id] != null && battleLayerConfig.towerLocal[l_id] > 0)
        {
          var l_block = l_layer4.getTileAt(cc.p(l_tx, l_ty));
          battleLayerConfig.highLight[l_numofblock] = l_block;
          battleLayerConfig.highLightID[l_numofblock] = l_id;
          ++l_numofblock;
        }
      }else
      {
        l_tx = l_x - 1;
        var l_ty = l_y + 1;
        var l_id = l_tx * battleLayerConfig.height + l_ty;
        if(battleLayerConfig.towerLocal[l_id] != null && battleLayerConfig.towerLocal[l_id] > 0)
        {
          var l_block = l_layer4.getTileAt(cc.p(l_tx, l_ty));
          battleLayerConfig.highLight[l_numofblock] = l_block;
          battleLayerConfig.highLightID[l_numofblock] = l_id;
          ++l_numofblock;
        }
      }
    }     
    if(l_numofblock == 4)
    {
      for(var i = 0; i < 4; ++ i)
      {
        var l_block = battleLayerConfig.highLight[i];
        var l_id = battleLayerConfig.highLightID[i];
        if(battleLayerConfig.occupiedOfblock[l_id] != 0)
        {
          battleLayerConfig.highLight[i] = null;
          battleLayerConfig.highLightID[i] = -1;
          -- l_numofblock;
          continue;
        }
      }
    }
    if(l_numofblock == 4)
    {
      for(var i = 0; i < 4; ++ i)
      {
        var l_block = battleLayerConfig.highLight[i];
        l_block.setVisible(true);
      }
    }
    return l_numofblock == 4;
  },
  // OpenGL坐标转成格子坐标
  StaggeredCoordForPosition:function(position)
  {
    var mapSize = this.TMXTiledMap.getMapSize();
    var tileSize = this.TMXTiledMap.getTileSize();
    var y = Math.floor( mapSize.height - 2 - Math.floor( ( (2 * Math.floor(position.y))/Math.floor(tileSize.height) ) ) );
    var x = position.x/tileSize.width - (y % 2)/2.0;
    x = Math.floor(x);
    return cc.p(x, y);
  },
    // tile坐标转成瓦片格子中心的OpenGL坐标
 /* Vec2 positionForStaggeredCoord(const Vec2& StaggeredCoord)
  {
    Size mapSize = tiledMap->getMapSize();
    Size tileSize = tiledMap->getTileSize();
    int x = StaggeredCoord.x*tileSize.width + ((int)StaggeredCoord.y%2)*tileSize.width/2;
    int y = (mapSize.height-(StaggeredCoord.y+1))*tileSize.height/2 - tileSize.height/2;
    return Vec2(x, y);
  }
  ,*/
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
