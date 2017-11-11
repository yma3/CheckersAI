//
// Created by New on 11/4/2017.
//

#ifndef CHECKERSAI_GAMEBOARD_H
#define CHECKERSAI_GAMEBOARD_H
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

//#include "Moves.h"

namespace std {
    template <typename T>
    std::string to_string(T val) {
        std::ostringstream s;
        s << val;
        return s.str();
    }
}

struct XY
{
    unsigned char x:4;
    unsigned char y:4;
    XY(unsigned char xx, unsigned char yy) {
        x = xx;
        y = yy;
    }
    XY(int i) {
        x = i&15;
        y = (i>>4)&15;
    }
    XY() {}
    std::string toString() {
        std::string sx = std::to_string((int)x);
        std::string sy = std::to_string((int)y);
        return "("+sx+" , "+sy+")";
    }
    bool equal(XY xy) {return x == xy.x && y == xy.y;}
    int toInt() { return y*16 + x; }

};

// to record the steps
class Step {
public:
	XY start;
	XY end;
	Step(XY startcc, XY endcc) { start = startcc; end = endcc; }
};

class Steps {
public:
	Steps() {}
	Steps(Steps &ns) {
		for (int i = 0; i<ns.steps.size(); ++i) {
			steps.push_back(ns.steps[i]);
		}
	}
	std::vector<Step > steps;
	void add(Step s) { steps.push_back(s); }
	void add(XY s, XY e) {
		Step step(s, e);
		add(step);
	}
	void print() {
		for (int i = 0; i<steps.size(); ++i) {
			Step t = steps[i];
			std::cout << t.start.toString() << ", " << t.end.toString()<< " ";
		}
	}
};

class PieceSteps {
public:
	int numberOfMoves; //for move steps
	Steps *steps[4];
	void add(Steps *p) {
		steps[numberOfMoves++] = p;
	}
	void print() {
		for (int i = 0; i<numberOfMoves; ++i) {
			Steps *t = steps[i];
			std::cout << std::endl << "move #: " << i << std::endl;
			t->print();
		}
	}

};

class GameBoard {
public:
    unsigned char board[8][8];
    int heuristicValue;
    XY P1_pieces[12];
    XY P2_pieces[12];
    int number_P1_pieces = 0;
    int number_P2_pieces = 0;
    bool player1 = true;
    int REGULAR, KINGVAL;
    bool hasAJump = false;
    bool isRoot = false;

    int numOfMoves = 0;
    int pathNum = 0;

    std::vector<GameBoard*> vectOfGb;
    //std::vector<std::vector<Moves>> listOfMoves;
	std::vector<PieceSteps *> listOfMoves;
	PieceSteps *currentPieceSteps;


    GameBoard(){}
    void setBoard(unsigned char myboard[][8]);
    void setHeuristic();
    int getHeuristic() {setHeuristic(); return heuristicValue;}

    void setPieces();
    XY* getP1Pieces() {return P1_pieces;}
    XY* getP2Pieces() {return P2_pieces;}

    void printPiece();
    void printBoard();
    void printInfo();
    
    void doMove(XY start, XY end);
	bool getMoves(Steps *theSteps, XY cc, unsigned char board[][8], std::vector<GameBoard*> &myvectofgb);//std::vector<std::vector<Moves>> &mylistOfMoves, int &moveNum, int &movePathNum);
    void getRegularMoves(XY cc, unsigned char board[][8], std::vector<GameBoard*> &myvectofgb);
    void getAllP1Moves();
    void getAllP2Moves();

    void printAllP1Moves();
    void printP1MoveList();

    bool isWin();
    //int alphabeta(GameBoard *gb, int depth, int alpha, int beta, bool isMax, int userplayer);


    void flipBoard();

    ///debug
    bool SameAsReg(GameBoard *parent);



};


#endif //CHECKERSAI_GAMEBOARD_H
