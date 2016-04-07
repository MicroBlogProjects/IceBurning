/**
 * Created by jiachen on 2016/3/29.
 */
//弃用
//管理所有的怪物
var ScheduleTime =1.0/10
var monsterManager;

var MonsterBackgroundLayer = cc.Layer.extend({
    myMonsterArray : null,
    enemyMonsterArray : null,
    m_clipperNode : null,
    ctor : function(){
        this._super();
        this.myMonsterArray = []; //创建一个数组
        this.enemyMonsterArray = [];
        this.init();
        monsterManager = this;

        this.schedule(this.updateEvent,ScheduleTime);//计时器
    },

    init :function(){
        config = MonsterConfig.maincity;
        var mainCitySprite =  new MonsterSprite(config,true);
        mainCitySprite.setPosition(150,GC.h_2);
        this.addChild(mainCitySprite);
        this.myMonsterArray.push(mainCitySprite);
    },

    addMonsterSprite : function(config, point, isOwnMonster){

        var mosterSprite;
        if(isOwnMonster){
            mosterSprite = new MonsterSprite(config,true);
        }
        else{
            mosterSprite = new MonsterSprite(config,false);
        }
        var offset = gamePlayLayer.scrollView.getInnerContainer().getPosition(); //计算当前scrollview的偏移
        mosterSprite.setPosition(point.x - offset.x ,point.y);
        this.addChild(mosterSprite);
        if(isOwnMonster)
            this.myMonsterArray.push(mosterSprite);
        else{
            this.enemyMonsterArray.push(mosterSprite);
        }
    },

    test : function(config, point){
        for(var i = 0; i < 10; i++){
            var randownum = Math.floor(Math.random() * 10000+1);
            var mosterSprite = new MonsterSprite(config,false);
            mosterSprite.setPosition(cc.p(randownum %(GC.w) + GC.w,randownum%640));
            //mosterSprite.setPosition(new cc.Point(200,200));
            this.addChild(mosterSprite);
            mosterSprite.walkingAnimate(mosterSprite);
            this.enemyMonsterArray.push(mosterSprite);
        }
        for(var i =0; i< 10; i++){
            var randownum = Math.floor(Math.random() * 10000+1);
            var mosterSprite = new MonsterSprite(config,true);
            mosterSprite.setPosition(cc.p(randownum %(GC.w),randownum%640));
            //mosterSprite.setPosition(new cc.Point(250,250));
            this.addChild(mosterSprite);
            mosterSprite.walkingAnimate();
            this.myMonsterArray.push(mosterSprite);
        }

    },

    updateEvent : function(){
        this.updateMonsterArray()
        this.monsterWalking();
    },

    updateMonsterArray :function(){
        //删除已经死亡的怪物
        for(var  i = 0; i < this.myMonsterArray.length; i++){
            var monster = this.myMonsterArray[i];
            if(monster.m_activity == false){
                this.myMonsterArray.splice(i,1);
            }
        }
        for(var  i = 0; i < this.enemyMonsterArray.length;i ++){
            var monster = this.enemyMonsterArray[i];
            if(this.enemyMonsterArray[i].m_activity == false){
                this.enemyMonsterArray.splice(i,1);
            }
        }
    },

    monsterWalking :function(){
        for(var i = 0;i < this.myMonsterArray.length; i++){
            var  myMonster = this.myMonsterArray[i];
            this.walk(myMonster,this.enemyMonsterArray);
        }
        for(var i = 0;i < this.enemyMonsterArray.length; i++){
            var  myMonster = this.enemyMonsterArray[i];
            this.walk(myMonster,this.myMonsterArray);
        }

    },

    walk : function(monster, enemyMonsterArray){
        if(monster.m_HP <= 0){
            monster.monsterAction(MonsterState.Death);
            return;
        }

        var sighRadius = monster.m_sightRadius;
        var attackRadius = monster.m_attackRadius;
        var monsterPoint = monster.getPosition();

        var destinationMonster = null;
        var minDistance  = sighRadius * sighRadius; //视野范围内

        for(var i = 0; i < enemyMonsterArray.length; i++){ //寻找最近的敌人
            var enemyMonster = enemyMonsterArray[i];
            if(enemyMonsterArray.m_HP <= 0){ //血量为0
                continue
            }

            var enemyPoint = enemyMonster.getPosition();
            var distance = this.getPointDistance(monsterPoint,enemyPoint);
            if (distance < minDistance){
                minDistance = distance  ;
                destinationMonster = enemyMonster;
            }
        }

        var destinationX;
        var destinationY;
        var destinationPoint;
        var state;
        if (destinationMonster == null){ //视野内没有任何敌人 向前走
            monster.setDirect();
            if(monster.m_isMyMonster){
                state = MonsterState.WalkingRight;
            }
            else{
                state = MonsterState.WalkingLeft;
            }
            destinationX = monsterPoint.x + monster.m_walkSpeed * ScheduleTime * monster.m_direct;
            destinationY = monsterPoint.y;
            destinationPoint = cc.p(destinationX,destinationY);
            monster.setPosition(destinationPoint);
        }
        else{
            var enemyPoint = destinationMonster.getPosition();
            if(minDistance <= (attackRadius * attackRadius)){ //攻击范围
                if(monsterPoint.x < enemyPoint.x){
                    state = MonsterState.AttackRight;
                }
                else{
                    state = MonsterState.AttackLeft;
                }
            }
            else{
                var dx = monsterPoint.x - enemyPoint.x;
                var dy = monsterPoint.y - enemyPoint.y;
                if(dx ==0){
                    if(dy > 0) //正下方
                    {

                    }
                    else{//正上方

                    }
                }
                else{
                    var d = monster.m_walkSpeed * ScheduleTime;
                    var ratio = dy / dx;
                    var x = Math.sqrt((d * d * 1.0) / (ratio * ratio +1));
                    var y = Math.sqrt((d * d - x * x));
                    if(dx < 0){
                        state = MonsterState.WalkingRight;
                        destinationX = monsterPoint.x + x;
                    }
                    else{
                        destinationX = monsterPoint.x - x;
                        state = MonsterState.WalkingLeft
                    }
                    if(dy < 0){
                        destinationY  =monsterPoint.y + y;
                    }
                    else{
                        destinationY  =monsterPoint.y - y;
                    }
                    destinationPoint = cc.p(destinationX,destinationY);
                    monster.setPosition(destinationPoint);
                }
            }
        }
        monster.monsterAction(state,destinationMonster);
    },

    getPointDistance : function (p1, p2) {
        return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
    },

    addClipperNode :function(){
        var pathConfig;
        if(GC.IS_HOST){
            pathConfig = HostPathConfig;
        }
        else {
            pathConfig = AwayPathConfig;
        }
        //设置模板
        var stencil = cc.Node.create();
        for(var i = 0; i<pathConfig.UpPath.length ;i++){
            var element = pathConfig.UpPath[i];
            var rectangular = this.getRectangular(cc.p(element.origin.x * TMXTileMapsize,element.origin.y * TMXTileMapsize),cc.p(element.destination.x * TMXTileMapsize,element.destination.y*TMXTileMapsize));
            stencil.addChild(rectangular);
        }
        for(var i =0 ;i < pathConfig.MiddlePath.length;i++){
            var element = pathConfig.MiddlePath[i];
            var rectangular = this.getRectangular(cc.p(element.origin.x * TMXTileMapsize,element.origin.y * TMXTileMapsize),cc.p(element.destination.x * TMXTileMapsize,element.destination.y*TMXTileMapsize));
            stencil.addChild(rectangular);
        }
        for(var i =0 ;i < pathConfig.DownPath.length;i++){
            var element = pathConfig.DownPath[i];
            var rectangular = this.getRectangular(cc.p(element.origin.x * TMXTileMapsize,element.origin.y * TMXTileMapsize),cc.p(element.destination.x * TMXTileMapsize,element.destination.y*TMXTileMapsize));
            stencil.addChild(rectangular);
        }
        //设置
        this.m_clipperNode = cc.ClippingNode.create(stencil);
        this.m_clipperNode.setInverted(true);//底板可见
        this.m_clipperNode.setAlphaThreshold(1.0);
        //设置灰色的底板
        var baLayer = cc.LayerColor.create(cc.color(0,0,0,150));
        baLayer.setScaleX(4);
        this.m_clipperNode.addChild(baLayer);
        this.addChild(this.m_clipperNode);
    },

    getRectangular : function(origin, destination){
        var rectangular = new cc.DrawNode();
        var origin = cc.p(origin);
        var destination = cc.p(destination);
        var color = cc.color(0,0,0);
        rectangular.drawRect(origin,destination,color);
        return rectangular;
    },

    removeClipperNode : function(){
        this.m_clipperNode.removeFromParent();
        this.m_clipperNode = null;
    }
});
