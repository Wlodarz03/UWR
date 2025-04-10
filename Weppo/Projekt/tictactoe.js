class ttt{

    turn; // 0 => 'X' , 1 => 'O'
    victory; // 1 kiedy wygra X, -1 kiedy wygra O (jezeli nie ma wygranego to 0)
    board;
    
    constructor(){
        this.turn = 0;
        this.board = [[" "," "," "],[" "," "," "],[" "," "," "]];
        this.victory = 0;
    }

    move(player,position){

        if (this.victory !=0){
            return;
        }
        let symbol = "X";
        if (player == 1){
            symbol = "O";
        }
        if (player != this.turn){
            return;
        }
        let pos = this.#formatPosition(position)
        if (pos == "fail") return;
        if (this.board[pos[0]][pos[1]] != " ") return;

        this.board[pos[0]][pos[1]] = symbol;
        this.turn=(this.turn+1)%2;
        this.#checkBoard();
        return;
    }

    #formatPosition(position){
        let x = position[0].charCodeAt(0)- 'a'.charCodeAt(0);
        let y = position[1]-'1';

        if (x<0 || x > 2 || y<0 || y>2){
            return "fail";
        }
        else return ""+x+y;
    }

    #checkBoard(){

        if (this.board[0][0]==this.board[0][1] && this.board[0][1]==this.board[0][2]){
            if (this.board[0][0]=="X"){
                this.victory=1;
            }
            if (this.board[0][0]=="O"){
                this.victory=-1;
            }
        }
        if (this.board[1][0]==this.board[1][1]&&this.board[1][1]==this.board[1][2])
        {
            if (this.board[1][0]=="X")
                this.victory=1;
            if (this.board[1][0]=="O")
                this.victory=-1;
        }
        if (this.board[2][0]==this.board[2][1]&&this.board[2][1]==this.board[2][2])
        {
            if (this.board[2][0]=="X")
                this.victory=1;
            if (this.board[2][0]=="O")
                this.victory=-1;
        }

        if (this.board[0][0]==this.board[1][0]&&this.board[1][0]==this.board[2][0])
        {
            if (this.board[0][0]=="X")
                this.victory=1;
            if (this.board[0][0]=="O")
                this.victory=-1;
        }
        if (this.board[0][1]==this.board[1][1]&&this.board[1][1]==this.board[2][1])
        {
            if (this.board[0][1]=="X")
                this.victory=1;
            if (this.board[0][1]=="O")
                this.victory=-1;
        }
        if (this.board[0][2]==this.board[1][2]&&this.board[1][2]==this.board[2][2])
        {
            if (this.board[0][2]=="X")
                this.victory=1;
            if (this.board[0][2]=="O")
                this.victory=-1;
        }

        if (this.board[0][0]==this.board[1][1]&&this.board[1][1]==this.board[2][2])
        {
            if (this.board[0][0]=="X")
                this.victory=1;
            if (this.board[0][0]=="O")
                this.victory=-1;
        }
        if (this.board[0][2]==this.board[1][1]&&this.board[1][1]==this.board[2][0])
        {
            if (this.board[0][2]=="X")
                this.victory=1;
            if (this.board[0][2]=="O")
                this.victory=-1;
        }
    }

    isFull(){
        let board = this.board;
        for (let i=0; i<board.length; i++){
            for (let j=0; j<board[i].length; j++){
                if (board[i][j] == " "){
                    return false;
                }
            }
        }
        return true;
    }

    getstate(){
        let board = this.board;
        let victory = this.victory;
        return {
            'board' : board,
            'victory' : victory
        }
    }
}

exports.ttt = ttt;