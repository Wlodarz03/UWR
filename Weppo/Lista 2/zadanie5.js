let obiekt ={
    prop: "val",
    method: function(){
        return "method"
    },
    get getter(){
        return this.prop
    },
    set setter(x){
        this.prop = x
    }
}

Object.defineProperties(obiekt, {
    prop2:{
        value: "val2",
        writable: true
    }
})

Object.defineProperties(obiekt,{
    method2:{
        value: function(){
            return "method2"
        }
    }
})

Object.defineProperties(obiekt,{
    gs: {
        get: function(){
            return this.prop2
        },
        set: function(x){
            this.prop2 = x
        }
    }
})

console.log(obiekt.gs)