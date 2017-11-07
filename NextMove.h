//
// Created by New on 11/5/2017.
//

#ifndef CHECKERSAI_NEXTMOVE_H
#define CHECKERSAI_NEXTMOVE_H
#include <iostream>
#include "Player1.h"

class NextMove {
public:
    GameBoard parent;
    Player1 p1;
    Player2 p2;
    //Composite possibleMoves;
    //Composite possibleMovesP2;
    //bool isJump = false;
    //bool isJumpP2 = false;
    //bool isMax = true;

    NextMove(GameBoard &gb):parent(gb),p1(gb),p2(gb){}

    void getNextMove (XY cc) {
        p1.getNextMove(cc);
        p2.getNextMove(cc);
    }
    void getNextJump (XY cc, Composite *jump) {
        p1.getNextJump(cc, jump);
        p2.getNextJump(cc, jump);
    }
    void createAllMoves() {
        p1.createAllMoves();
        p2.createAllMoves();
    }
    //void checkMoves();
    void printMoves() {
        std::cout << std::endl << "== PLAYER 1 MOVES ==";
        p1.printMoves();
        //std::cout << std::endl << "== PLAYER 2 MOVES ==";
        //p2.printMoves();
    }
};


#endif //CHECKERSAI_NEXTMOVE_H
