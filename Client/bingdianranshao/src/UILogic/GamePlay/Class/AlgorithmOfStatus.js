/**
 * Created by OPAS on 2016/4/11.
 */
 var algorithmOfStatus;
 var TurnOnRoad = null;
 var AlgorithmOfStatus = cc.Class.extend({
    mapstatus:null,
    towerOccupiedblock:null,
    queue:null,
    bfsmap:null,
    bfsmark:null,
     Q :null,
    makrid:null,
    makrid2:null,
    makrdir:null,
    ctor:function()
    {
      this.makrid=1;
      this.makrid2 =1;
      this.Q = new MyQueue(100);
       this.queue=new MyQueue(50);
       algorithmOfStatus = this;
       TurnOnRoad={};
       TurnOnRoad[0]=[];
       TurnOnRoad[1]=[];
       TurnOnRoad[0].push(cc.p(-1,-1));
       TurnOnRoad[0].push(cc.p(0,-1));
       TurnOnRoad[0].push(cc.p(0,1));
       TurnOnRoad[0].push(cc.p(-1,1));

       TurnOnRoad[1].push(cc.p(0,-1));
       TurnOnRoad[1].push(cc.p(1,-1));
       TurnOnRoad[1].push(cc.p(0,1));
       TurnOnRoad[1].push(cc.p(1,1));
       this.mapstatus={};
       this.mapstatus[0]={};
       this.mapstatus[1]={};
       this.towerOccupiedblock={};
       this.bfsmap=new Array();
       this.bfsmark=new Array();
       this.makrdir=new Array();
       for(var k = 0; k <2; ++ k)
       for(var i = 0; i < 30; ++i)
       {
            this.mapstatus[k][i]={};
            this.towerOccupiedblock[i]={};
            for(var j = 0; j < 40; ++j)
            {   
                if(k==0)
                {
                  this.bfsmap.push(0);
                  this.bfsmark.push(0);
                  this.makrdir.push(0);
                }
                this.mapstatus[k][i][j]=[];
                this.towerOccupiedblock[i][j]=false;
            }      
       }
    },
    AddMonster:function(sprite,op)
    {
       if(op > 0)
       {
          for(var i = 0; i < sprite.m_TiledPosition.length; ++i)
          {
            var l_x = sprite.m_TiledPosition[i].x;
            var l_y = sprite.m_TiledPosition[i].y;
            this.mapstatus[sprite.m_Camp][l_x][l_y].push(sprite.m_spriteID); 
          }

       }else{
         for(var i = 0; i < sprite.m_TiledPosition.length; ++i)
         {
            var l_x = sprite.m_TiledPosition[i].x;
            var l_y = sprite.m_TiledPosition[i].y;
            for(var j = 0; j < this.mapstatus[sprite.m_Camp][l_x][l_y].length; ++j)
            {
               if(this.mapstatus[sprite.m_Camp][l_x][l_y][j] == sprite.m_spriteID)
               {
                  this.mapstatus[sprite.m_Camp][l_x][l_y].splice(j,1);
                  break;
               }
            }
         }
       }
    },
    PushDownTower:function(tiled,op)
    {
       if(op > 0 )
       {
          for(var i = 0; i< tiled.length; ++ i)
          {
            var l_x = tiled[i].x;
            var l_y = tiled[i].y;
            this.towerOccupiedblock[l_x][l_y] = true;
          }
       }else
       {
          for(var i = 0; i< tiled.length; ++ i)
          {
            var l_x = tiled[i].x;
            var l_y = tiled[i].y;
            this.towerOccupiedblock[l_x][l_y] = false;
          }
       }
    },
    DistanceOfPoint:function(p1, p2)
    {
        if(p1.x > p2.x) 
        {
          var tmp = p1; p1 = p2; p2 = tmp;
        }
        var pre = 2 * (p2.x - p1.x);
        if((p1.y + p2.y) % 2 == 1)
        {
          if(p2.y % 2 == 1) pre = pre + 1;
          else pre = pre - 1;
        }
        var ans = pre;
        var dif = Math.abs(p1.y - p2.y);
        if(dif > pre)
        {
          ans = dif;
        }
        return ans;
    },
    DistanceOfSprite:function(sp1,sp2)
    {
      var dis = 10000;
      for (var i = 0; i < sp1.m_TiledPosition.length; ++i) {
        for (var j = 0; j < sp2.m_TiledPosition.length; ++j) {
          var p1 = sp1.m_TiledPosition[i];
          var p2 = sp2.m_TiledPosition[j];
          var tmp = this.DistanceOfPoint(p1, p2);
          dis = Math.min(dis, tmp);
        }
      }
      return dis;
    }
    ,
    IsAttack:function(sprite)
    {
       if(sprite.m_AttackObjectsID != -1)
       {
          var l_obj = monsterManager.IdMapSprite[ sprite.m_AttackObjectsID ];
          if(l_obj != null && l_obj.m_HP > 0 && this.DistanceOfSprite(sprite,l_obj) <= sprite.m_attackRadius)
          {
            return true;
          }else{
            sprite.m_nextState = null;
            sprite.m_AttackObjectsID = -1;    
          }
       }
      if(sprite.m_id < 100)
       {
         var l_attacknum = 0;
         var l_x = sprite.m_TiledPosition[0].x;
         var l_y = sprite.m_TiledPosition[0].y;
         if(this.towerOccupiedblock[l_x][l_y]) return false;
         for(var k = 0; k < 2; ++ k)
         for(var i = 0; i < this.mapstatus[k][l_x][l_y].length; ++i)
         {
            var l_id = this.mapstatus[k][l_x][l_y][i];
            var l_obj = monsterManager.IdMapSprite[ l_id ];
            if(l_obj.m_AttackObjectsID != -1)
              ++ l_attacknum;
         }
         if(l_attacknum >= GC.NUM_MONSTER_BLOCK)
         {
           return false;
         }
       }
       for(var i = 0;  i < sprite.m_TiledPosition.length; ++i)
       {
          var id = this.Around(sprite.m_TiledPosition[i],sprite.m_attackRadius,sprite.m_attackRadius,1-sprite.m_Camp);
         if(id<0) continue;
         //cc.log("my =" + sprite.m_id + id);
         sprite.m_AttackObjectsID = id;
         return true;
       }
       return false
    },
    TurnLeft:function(pos)
    {
        if(pos.y%2){
          return cc.p(pos.x,pos.y+1);
        }else{
          return cc.p(pos.x-1,pos.y+1);
        }
    },
    TurnRight:function(pos)
    {
       if(pos.y%2){
          return cc.p(pos.x+1,pos.y-1);
       }else{
          return cc.p(pos.x, pos.y-1);
       }
    },
    TurnUP:function(pos)
    {
       if(pos.y%2)
       {
          return cc.p(pos.x, pos.y-1);
       }else{
          return cc.p(pos.x-1,pos.y-1);
       }
    },
    TurnDown:function(pos)
    {
        if(pos.y%2)
        {
          return cc.p(pos.x+1,pos.y+1);
        }else{
          return cc.p(pos.x, pos.y+1);
        }      
    },
    TurnLU:function(pos)
    {
        return cc.p(pos.x-1,pos.y);
    },
    TurnRU:function(pos)
    {
        return cc.p(pos.x, pos.y-2);
    },
    TurnLD:function(pos)
    {
        return cc.p(pos.x, pos.y+2);
    },
    TurnRD:function(pos)
    {
        return cc.p(pos.x+1, pos.y);
    },
    TurnDirec:function(pos,dir)
    {

        if(dir == 0)
        return this.TurnUP(pos);
        else if(dir == 1)
        return this.TurnRight(pos);
        else if(dir == 2)
          return this.TurnDown(pos);
        else return this.TurnLeft(pos);
    },
    GetIdByTiledPos:function(l_pos)
    {
      return l_pos.x * battleLayerConfig.height + l_pos.y;
    }
    ,
    GetAttrackDir:function(sprite)
    {
       
        var l_obj = monsterManager.IdMapSprite[sprite.m_AttackObjectsID];
        var l_p2 = l_obj.m_TiledPosition[0];
        var l_p1 = sprite.m_TiledPosition[0];
        if(l_p1.x == l_p2.x )
        {
          if(l_p1.y%2)
          {
             sprite.m_nextState = MonsterState.AttackLeft;
             sprite.m_direct = -1;

          }else{
             sprite.m_nextState = MonsterState.AttackRight;
             sprite.m_direct = 1;
          }
        }else{
          if(l_p1.x > l_p2.x)
          {
             sprite.m_nextState = MonsterState.AttackLeft;
             sprite.m_direct = -1;
          }else{
             sprite.m_nextState = MonsterState.AttackRight;
             sprite.m_direct = 1;
          }
        }

    }
    ,
    GetStatus:function(sprite)
    {
      if(sprite.m_state != null)
        return ;
       var l_jud = this.IsAttack(sprite);
       if(l_jud || sprite.m_id > 100 ) 
       {
           if(l_jud)
           {
             this.GetAttrackDir(sprite);
           }
           return;
       }
      this.GetNextLocation(sprite);

    },
    JudStandOn:function(pos)
    {
      var l_attacknum = 0;
      var l_x = pos.x;
      var l_y = pos.y;
      if(this.towerOccupiedblock[l_x][l_y]) return false;
      for(var k = 0; k < 2; ++ k)
      for(var i = 0; i < this.mapstatus[k][l_x][l_y].length; ++i)
      {
        var l_id = this.mapstatus[k][l_x][l_y][i];
        var l_obj = monsterManager.IdMapSprite[ l_id ];
        if(l_obj.m_AttackObjectsID != -1)
          ++ l_attacknum;
      }
      if(l_attacknum >= GC.NUM_MONSTER_BLOCK)
      {
         return false;
      }
      return true;
    },
    Around:function(pos,W,H,camp)
    {

       var l_W = W;
       var l_H = H;
       var l_nex = pos;
       for(var i = 0; i<H; i++)
       {
          pos = this.TurnUP(pos);
       }
       for(var i = 0; i<W; i++)
       {
          pos = this.TurnLeft(pos);
       }

       for(var i = 0; i <= W*2; i++)
       {   
          l_nex = pos;
          var l_h = l_H;
          for(var j = 0; j <= 2*H; ++j)
          {
             if((l_nex.x >= battleLayerConfig.width || l_nex.x < 0 || l_nex.y < 0 || l_nex.y >= battleLayerConfig.height)==false)   
             {
                  if(this.mapstatus[camp][l_nex.x][l_nex.y].length>0 && (Math.abs(l_W) + Math.abs(l_h) <= l_H))
                    {
                      for(var e = 0; e < this.mapstatus[camp][l_nex.x][l_nex.y].length ; ++e)
                        {
                          var l_id = this.mapstatus[camp][l_nex.x][l_nex.y][e];
                          var l_obj = monsterManager.IdMapSprite[l_id];
                          if(l_obj.m_HP > 0)
                            {
                             // cc.log("loc x= "+l_nex.x+" y= "+l_nex.y +" e= " +this.mapstatus[camp][l_nex.x][l_nex.y][e]);
                              return this.mapstatus[camp][l_nex.x][l_nex.y][e];
                            }
                        }
                    }
             }
             l_nex=this.TurnDown(l_nex);
             l_h --;
          }
         pos=this.TurnRight(pos);
         l_W --;
       }
       return -1;
    },
    BFSViewFile:function(sprite)
    {

        this.Q.clear();        
        for(var j = 0; j < 4; j ++)
        {
          var l_nex = this.TurnDirec(sprite.m_TiledPosition[0],j);
          if(l_nex.x >= battleLayerConfig.width || l_nex.x < 0 || l_nex.y < 0 || l_nex.y >= battleLayerConfig.height)
                continue;
          this.bfsmark[ this.GetIdByTiledPos(l_nex) ] = this.makrid2;
          this.makrdir[ this.GetIdByTiledPos(l_nex) ] = j + 1;
          this.Q.push( l_nex ); 
        }
        var l_tildpos = sprite.m_TiledPosition[0];
        while(this.Q.length > 0)
        {
          var front = this.Q.shift();
          if(this.JudStandOn(front))
          {
            var d= [];
            d.push(front);
            var id = this.Around(front,sprite.m_attackRadius,sprite.m_attackRadius,1-sprite.m_Camp);
            if(id >= 0 ) return this.makrdir[ this.GetIdByTiledPos( front ) ] - 1;
          }
          for(var i = 0; i < 4; ++ i)
          {
            var l_nex = this.TurnDirec(front,i);
            if(l_nex.x >= battleLayerConfig.width || l_nex.x < 0 || l_nex.y < 0 || l_nex.y >= battleLayerConfig.height)
                continue;
            var diff = this.DistanceOfPoint(l_tildpos, l_nex);
            var l_mark = this.bfsmark[this.GetIdByTiledPos(l_nex) ];
            if( l_mark != this.makrid2 && diff <= sprite.m_sightRadius && this.towerOccupiedblock[l_nex.x][l_nex.y]!=true)
            {
              this.Q.push(l_nex);
              this.bfsmark[this.GetIdByTiledPos(l_nex) ] = this.makrid2;
              this.makrdir[this.GetIdByTiledPos(l_nex)] = this.makrdir[this.GetIdByTiledPos(front)];
            }
          }
        } 
        this.makrid2++;
        return -1;
    }
    ,
    GetNextLocation:function(sprite)
    {
        var l_nex = this.BFSViewFile(sprite);

        if( l_nex == -1)
        {
          if(sprite.m_state != null)return ;
          var l_tiledPosition = sprite.m_TiledPosition[0];
          var l_id = this.GetIdByTiledPos(l_tiledPosition);
          if(battleLayerConfig.roadLocal[l_id] > 0)
          {      
              this.GetNextLocationOnRoad(sprite);
          }else
          {
              this.GetNextLocationNotOnRoad(sprite, battleLayerConfig.endPoint[sprite.m_Camp]);
          }
        }else{

          sprite.m_nextTiledPosition[0] = this.TurnDirec(sprite.m_TiledPosition[0], l_nex);
        }
        this.GetDirctAndStatusMonster(sprite);
    },
    GetNextLocationOnRoad:function(sprite)
    {
        var l_tiledPosition = sprite.m_TiledPosition[0];   
        var l_minid = 10000000;
        var l_maxid = -1;
        var l_minposition;
        var l_maxposition;
        var l_IdArray=[];
        var l_posArray=[];
        var l_idx = l_tiledPosition.y%2; 
        for(var i = 0; i < 4; ++ i)
        {
            var l_tu = TurnOnRoad[l_idx][i];
            var l_x = l_tiledPosition.x + l_tu.x;
            var l_y = l_tiledPosition.y + l_tu.y;
            var l_id = l_x * battleLayerConfig.height + l_y;
            if(battleLayerConfig.roadLocal[l_id]>0)
            {
                l_IdArray.push(l_id);
                l_posArray.push(cc.p(l_x, l_y));
            }
        }
        for(var i = 0; i < l_IdArray.length; ++ i)
        {
            if(l_maxid < l_IdArray[i])
            {
                l_maxid = l_IdArray[i];
                l_maxposition = l_posArray[i];
            }
            if(l_minid > l_IdArray[i])
            {
                l_minid = l_IdArray[i];
                l_minposition = l_posArray[i];
            }
        }
        if(sprite.m_Camp == 0)
        {
            sprite.m_nextTiledPosition[0] = l_maxposition;
        }else
        {
            sprite.m_nextTiledPosition[0] = l_minposition;
        }
    },
    GetNextLocationNotOnRoad:function(sprite,l_endPosition)
    {
      var l_minv =1000000;
      var l_minpos = null;
      var l_mypos = sprite.m_TiledPosition[0];
      for(var i = 0; i < 4; i++)
      {
          var l_tit = this.TurnDirec(l_mypos,i);
          var diff = this.DistanceOfPoint(l_tit, l_endPosition);
          if(diff < l_minv && l_tit.x >=0 && l_tit.x <= battleLayerConfig.width && l_tit.y >=0 && l_tit.y <= battleLayerConfig.height)
          {
            l_minv = diff;
            l_minpos = l_tit;
          }
      }
      sprite.m_nextTiledPosition[0] = l_minpos;
    },
    GetDirctAndStatusMonster:function(sprite)
    {
        if(sprite.m_nextTiledPosition[0].x == sprite.m_TiledPosition[0].x)
        {
           if(sprite.m_TiledPosition[0].y%2)
           {
              sprite.m_direct = -1;
              sprite.m_nextState = MonsterState.WalkingLeft;
           }else{
              sprite.m_direct = 1;
              sprite.m_nextState = MonsterState.WalkingRight;
           }

        }else{
          if(sprite.m_nextTiledPosition[0].x > sprite.m_TiledPosition[0].x)
          {
            sprite.m_direct = 1;
            sprite.m_nextState = MonsterState.WalkingRight;
          }else{
            sprite.m_direct = -1;
            sprite.m_nextState = MonsterState.WalkingLeft;

          }
        }
    }
 });