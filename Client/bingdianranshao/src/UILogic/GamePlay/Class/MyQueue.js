var MyQueue = cc.Class.extend({
    Q:null,
    front:0,
    tail:0,
    length:0,
    num:0,
    ctor:function(len){
        this.length = 0;
        this.Q = [];
        this.front= 0;
        this.tail = 0;
        this.num = len;
        for (var i = 0; i < len; ++i) {
            this.Q[i] = 0;
        }
    },
    pop:function() {
        if(this.front != this.tail) {
            this.tail = (this.tail - 1 + this.num) % this.num;
            this.length--;
            return this.Q[this.tail];
        }
        return null;
    },
    shift:function() {
        if(this.front != this.tail) {
            var ret = this.Q[this.front];
            this.front = (this.front + 1) % this.num; 
            this.length--;
            return ret;
        }
        return null;
    },
    clear:function(){
        this.length=0;
        this.front = this.tail = 0;
    },
    push:function(pos){
        this.length++;
        this.Q[this.tail] = pos;
        this.tail=(this.tail+1)%this.num;
        if(this.tail == this.front )
        {
            //cc.log("MyQueue out of num");
        }
    }

});