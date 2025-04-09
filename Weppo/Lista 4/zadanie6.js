function Tree(val, left, right) {
    this.left = left;
    this.right = right;
    this.val = val;
}

Tree.prototype[Symbol.iterator] = function*() {
    var q = []
    q.push(this)
    while(q.length > 0){
        node = q.shift() // zwraca pierwszy element i wywala go z tablicy
        yield node.val

        if(node.right)
            q.push(node.right)

        if(node.left)
            q.push(node.left)
    }
}

//          1
//       2     4
//    3

var root = new Tree( 1, new Tree( 2, new Tree( 3 ) ), new Tree( 4 ));

for ( var e of root ) {
    console.log( e );
}