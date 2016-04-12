/**
 * Created by jiachen on 2016/4/11.
 */



var checkPathManager;
var CheckPathManager = cc.Class.extend({

    walkingPathConfig : null,
    fightingPathConfig : null,
    buildingPositionConfig : null,
    buildingPositionMark : null, //标记是否被放塔

    ctor :function(){
        this.buildingPositionMark = [];

        this.fightingPathConfig = FightingPathConfig;
        if(GC.IS_HOST){
            this.walkingPathConfig = HostPathConfig;
            this.buildingPositionConfig = HostBuilddingPosition;
        }
        else {
            this.walkingPathConfig = AwayPathConfig;
            this.buildingPositionConfig = AwayBuilddingPosition;
        }
        for(var i = 0; i<this.buildingPositionConfig.length;i++){
            this.buildingPositionMark.push(false);
        }
        checkPathManager = this;
    },


    //是否在范围内
    isInRect : function(config,point){
        var origin = config.origin;
        var destination = config.destination;
        var rect = cc.rect(origin.x * TMXTileMapsize, origin.y * TMXTileMapsize,(destination.x - origin.x) *TMXTileMapsize,(destination.y - origin.y) * TMXTileMapsize);
        return cc.rectContainsPoint(rect, point);
    },

    //行走或者攻击的判断是否在向上走的路
    isInUpPath : function (pathConfig,point){
        for(var i = 0; i<pathConfig.UpPath.length ;i++){
            var element = pathConfig.UpPath[i];
            if(this.isInRect(element,point)){
                return true;
            }
        }
        return false;
    },
    isInStraightPath : function(pathConfig,point){
        for(var i =0 ;i < pathConfig.StraightPath.length;i++){
            var element = pathConfig.StraightPath[i];
            if(this.isInRect(element,point)){
                return true;
            }
        }
        return false;
    },
    isInDownPath : function(pathConfig,point){
        for(var i =0 ;i < pathConfig.DownPath.length;i++){
            var element = pathConfig.DownPath[i];
            if(this.isInRect(element,point)){
                return true;
            }
        }
        return false;
    },

    isInPath : function(pathConfig,point){
        if((this.isInUpPath(pathConfig,point)) || (this.isInStraightPath(pathConfig,point)) || (this.isInDownPath(pathConfig,point))){
            return true;
        }
        else{
            return false;
        }
    },

    isInFightUpPath : function(point){
      return this.isInUpPath(this.fightingPathConfig, point);
    },

    isInFightDownPath : function(point){
        return this.isInDownPath(this.fightingPathConfig,point);
    },

    isInWalkingPath : function(point){
        return this.isInPath(this.walkingPathConfig, point);
    },

    isInFightPath :function(point){
        return this.isInPath(this.fightingPathConfig,point);
    },


    isInBuildingPosition : function(buildingConfig,point){
        for(var i = 0; i < buildingConfig.length; i++){
            var element = buildingConfig[i];
            if(this.isInRect(element,point)){
                return i;
            }
        }
        return -1;
    },

    //判断是否能放塔
    isInTowerPosition : function(point){
        var ret = this.isInBuildingPosition(this.buildingPositionConfig,point);
        if(ret == -1){
            return null;
        }
        else {
            this.buildingPositionMark[ret] = true;
            var element = this.buildingPositionConfig[ret];
            var position = cc.p((element.origin.x+1)*TMXTileMapsize,(element.origin.y+1)*TMXTileMapsize);
            return position;
        }
    },

    resetBuildingPosition : function(monster){
        if(monster.m_type == MonsterType.Building) {
            var ret = this.isInBuildingPosition(this.buildingPositionConfig, monster.getPosition());
            if (ret != -1) {
                this.buildingPositionMark[ret] = false;
            }
        }
    },

    getStencil : function(){
        var stencil = cc.Node.create();
        for(var i = 0; i<this.walkingPathConfig.UpPath.length ;i++){
            var element = this.walkingPathConfig.UpPath[i];
            var rectangular = this.getRectangular(cc.p(element.origin.x * TMXTileMapsize,element.origin.y * TMXTileMapsize),cc.p(element.destination.x * TMXTileMapsize,element.destination.y*TMXTileMapsize));
            stencil.addChild(rectangular);
        }
        for(var i =0 ;i < this.walkingPathConfig.StraightPath.length;i++){
            var element = this.walkingPathConfig.StraightPath[i];
            var rectangular = this.getRectangular(cc.p(element.origin.x * TMXTileMapsize,element.origin.y * TMXTileMapsize),cc.p(element.destination.x * TMXTileMapsize,element.destination.y*TMXTileMapsize));
            stencil.addChild(rectangular);
        }
        for(var i =0 ;i < this.walkingPathConfig.DownPath.length;i++){
            var element = this.walkingPathConfig.DownPath[i];
            var rectangular = this.getRectangular(cc.p(element.origin.x * TMXTileMapsize,element.origin.y * TMXTileMapsize),cc.p(element.destination.x * TMXTileMapsize,element.destination.y*TMXTileMapsize));
            stencil.addChild(rectangular);
        }
        return stencil;
    },

    //画一个矩形
    getRectangular : function(origin, destination){
        var rectangular = new cc.DrawNode();
        var origin = cc.p(origin);
        var destination = cc.p(destination);
        var color = cc.color(0,0,0);
        rectangular.drawRect(origin,destination,color);
        return rectangular;
    }

});
