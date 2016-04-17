/**
 * Created by OPAS on 2016/4/11.
 */
 var algorithmOfStatus;
 var TurnOnRoad = null;
 var AlgorithmOfStatus = cc.Class.extend({
    ctor:function()
    {
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
    },     
    GetNextLocation:function(sprite)
    {
        if(sprite.m_state != null)return ;
        sprite.m_direct = sprite.m_Camp == 0 ? 1:-1;
        sprite.m_nextState = sprite.m_Camp == 0 ? MonsterState.WalkingRight:MonsterState.WalkingLeft;
        var l_tiledPosition = sprite.m_TiledPosition[0];
        var l_id = l_tiledPosition.x * battleLayerConfig.height + l_tiledPosition.y;
        if(battleLayerConfig.roadLocal[l_id] > 0)
        {      
            this.GetNextLocationOnRoad(sprite);
        }else
        {
            this.GetNextLocationNotOnRoad(sprite);
        }
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
            sprite.m_TiledPosition[0] = l_maxposition;
        }else
        {
            sprite.m_TiledPosition[0] = l_minposition;
        }
    },
    GetNextLocationNotOnRoad:function(sprite)
    {
        var l_tiledPosition = sprite.m_TiledPosition[0];
        var l_idx = sprite.m_Camp == 0 ? 0:1;
        var l_endPosition = battleLayerConfig.endPoint[l_idx]; 
        var l_diffx = l_tiledPosition.x - l_endPosition.x;
        l_diffx = l_diffx > 0 ? l_diffx : -l_diffx;
        var l_diffy = l_tiledPosition.y - l_endPosition.y;
        l_diffy = l_diffy > 0 ? l_diffy : -l_diffy;
        var l_nowTilePosition;
        if(l_diffx >= l_diffy)
        {
            l_nowTilePosition = (l_tiledPosition.x - 1)*battleLayerConfig.height + l_tiledPosition.y;
            sprite.m_TiledPosition[0] = cc.p((l_tiledPosition.x - 1), l_tiledPosition.y);

        }else
        {
            var l_jud = l_tiledPosition.y > l_endPosition.y ? 1 : -1;
            sprite.m_TiledPosition[0] = cc.p(l_tiledPosition.x ,(l_tiledPosition.y - l_jud));
        }
    }
 });