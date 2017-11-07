//
// Created by New on 11/4/2017.
//

#ifndef CHECKERSAI_PLAYER_H
#define CHECKERSAI_PLAYER_H
#include "GameBoard.h"
#include "Composite.h"
#include <vector>

class MoveBase {
public:
    GameBoard &parent;
    Composite possibleMoves;
    bool isJump = false;
    bool isKing;
    virtual void getNextMove (XY cc) = 0;
    virtual void getNextJump (XY cc, Composite *jump) = 0;
    virtual void createAllMoves() = 0;
    virtual void printMoves() = 0;

    MoveBase(GameBoard &p):parent(p),possibleMoves(false){}
};

class Player1:public MoveBase {
public:
    static const int REGULAR = 2; int KINGVAL = 4;
    Player1(GameBoard &p):MoveBase(p) {}
    void getNextMove(XY cc);
    void getNextJump(XY cc, Composite *jump);
    void createAllMoves();
    void printMoves();
    Composite *getOneJumpMoveList(int i);
    void getOneMoveList(int i);
    void clean() {
        possibleMoves.clean();
    }
    std::vector <Composite*> leaflist;
};

class Player2:public MoveBase {
public:
    static const int REGULAR = 1; int KINGVAL = 3;
    Player2(GameBoard &p):MoveBase(p) {}
    void getNextMove(XY cc);
    void getNextJump(XY cc, Composite *jump);
    void createAllMoves();
    void printMoves();
};





#endif //CHECKERSAI_PLAYER_H
