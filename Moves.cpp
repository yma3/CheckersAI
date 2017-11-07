#include "Moves.h"


/*void Moves::doMove(GameBoard &parent) {





}*/

/*void Moves::getMoves(XY cc, GameBoard &parent) {

    if (cc.x > 0 && cc.y > 0) {
        XY xy(cc.x - 1, cc.y - 1);
        int v = parent.board[xy.x][xy.y];
        if ((v == REGULAR || v == KINGVAL) && parent.board[xy.x - 1][xy.y - 1] == 0 && (xy.x > 0 && xy.y > 0)) {
            //ADD JUMP
            XY zz(xy.x - 1, xy.y - 1);
            if (jump == NULL || (possibleMoves.isNotLoop(zz) && cc.equal(jump->origin))) {
                jump = new Composite(true, cc);
                possibleMoves.add(jump);
                isJump = true;
            }
            bool isAdded = jump->add(new Leaf(cc, zz));
            if(isAdded)
                getNextJump(zz, jump);
        }
    }
    //TOP RIGHT
    if (cc.x > 0 && cc.y < 7) {
        XY xy(cc.x - 1, cc.y + 1);
        int v = parent.board[xy.x][xy.y];
        if ((v == REGULAR || v == KINGVAL) && parent.board[xy.x - 1][xy.y + 1] == 0 && (xy.x > 0 && xy.y < 7)) {
            //ADD JUMP
            XY zz(xy.x - 1, xy.y + 1);
            if (jump == NULL || (possibleMoves.isNotLoop(zz) && cc.equal(jump->origin))) {
                jump = new Composite(true, cc);
                possibleMoves.add(jump);
                isJump = true;
            }
            bool isAdded = jump->add(new Leaf(cc, zz));
            if(isAdded)
                getNextJump(zz, jump);
        }
    }
    if (!isKing) return;
    //BOTTOM LEFT
    if (cc.x < 7 && cc.y > 0) {
        XY xy(cc.x + 1, cc.y - 1);
        int v = parent.board[xy.x][xy.y];
        if ((v == REGULAR || v == KINGVAL) && parent.board[xy.x + 1][xy.y - 1] == 0 && (xy.x < 7 && xy.y > 0)) {
            //ADD JUMP
            XY zz(xy.x + 1, xy.y - 1);
            if (jump == NULL || (possibleMoves.isNotLoop(zz) && cc.equal(jump->origin))) {
                jump = new Composite(true, cc);
                possibleMoves.add(jump);
                isJump = true;
            }
            bool isAdded = jump->add(new Leaf(cc, zz));
            if(isAdded)
                getNextJump(zz, jump);
        }
    }
    //BOTTOM RIGHT
    if (cc.x < 7 && cc.y < 7) {
        XY xy(cc.x + 1, cc.y + 1);
        int v = parent.board[xy.x][xy.y];
        if ((v == REGULAR || v == KINGVAL) && parent.board[xy.x + 1][xy.y + 1] == 0 && (xy.x < 7 && xy.y < 7)) {
            //ADD JUMP
            XY zz(xy.x + 1, xy.y + 1);
            if (jump == NULL || (possibleMoves.isNotLoop(zz) && cc.equal(jump->origin))) {
                jump = new Composite(true, cc);
                possibleMoves.add(jump);
                isJump = true;
            }
            bool isAdded = jump->add(new Leaf(cc, zz));
            if(isAdded)
                getNextJump(zz, jump);
        }
    }


}*/