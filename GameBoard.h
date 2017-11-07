//
// Created by New on 11/4/2017.
//

#ifndef CHECKERSAI_GAMEBOARD_H
#define CHECKERSAI_GAMEBOARD_H
#include <string>
#include <sstream>
#include <iostream>

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

class GameBoard {
public:
    unsigned char board[8][8];
    int heuristicValue;
    XY P1_pieces[12];
    XY P2_pieces[12];
    int number_P1_pieces = 0;
    int number_P2_pieces = 0;

    GameBoard(){}
    void setBoard(unsigned char myboard[][8]);
    void setHeuristic();
    int getHeuristic() {return heuristicValue;}

    void setPieces();
    XY* getP1Pieces() {return P1_pieces;}
    XY* getP2Pieces() {return P2_pieces;}

    void printPiece();
    void printBoard();

    int topRight(XY xy, int dist) {

    }

    void flipBoard();

    void doMove(XY start, XY end) {
        std::cout<<"DOING MOVE" << start.toString() << " , " << end.toString() << std::endl;
        int dx = end.x - start.x;
        if(dx == 2 || dx == -2) {
            board[(start.x+end.x)/2][(start.y+end.y)/2] = 0;
        }
        board[end.x][end.y] = board[start.x][start.y];
        board[start.x][start.y] = 0;
    }
};


#endif //CHECKERSAI_GAMEBOARD_H
