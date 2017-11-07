#include <iostream>
#include <string>
#include <sstream>

#include "GameBoard.h"
#include "Player1.h"
#include "CheckerComposite.h"
#include "P1NextBoards.h"

void initialize(GameBoard &gb) {
    //INITIAL BOARD
    unsigned char initialBoard[8][8] = {
            {0, 2, 0, 2, 0, 2, 0, 2},
            {2, 0, 2, 0, 2, 0, 2, 0},
            {0, 2, 0, 2, 0, 2, 0, 2},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 1, 0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 0}
    };

    // JUMP TEST BOARD
    unsigned char testJumpBoard[8][8] = {
            {0, 2, 0, 2, 0, 2, 0, 2},
            {0, 0, 1, 0, 0, 0, 2, 0},
            {0, 2, 0, 2, 0, 2, 0, 2},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 2, 0, 2, 0, 0},
            {1, 0, 1, 0, 3, 0, 1, 0},
            {0, 1, 0, 2, 0, 1, 0, 1},
            {1, 0, 0, 0, 1, 0, 1, 0}
    };
    unsigned char testSquareJumpBoard[8][8] = {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 2, 0, 2, 0, 2, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 2, 0, 2, 0, 0},
            {0, 0, 0, 0, 3, 0, 0, 0},
            {0, 0, 0, 2, 0, 2, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0}
    };
    //gb.setBoard(initialBoard);
    //gb.setBoard(testJumpBoard);
    gb.setBoard(testSquareJumpBoard);
    gb.setPieces();
    gb.setHeuristic();

}

void doTestNextMove(GameBoard &playingboard) {
    Player1 p1(playingboard);
    Player2 p2(playingboard);

    p1.createAllMoves();
    p2.createAllMoves();

    std::cout << std::endl << "== PLAYER 1 MOVES ==";
    p1.printMoves();
    //std::cout << std::endl << "== PLAYER 2 MOVES ==";
    //p2.printMoves();
    //playingboard.flipBoard();
}

int requestMoveInput() {
    std::string input = "";
    int maxsize = 5;

    while(true) {
        std::cout << "Please Enter Your Move: ";
        getline(std::cin, input);

        std::stringstream myStream(input);
        if(myStream >> maxsize)
            break;
        std::cout << "Invalid entry. Try again" << std::endl;
    }
    return 0;
}




int main () {

    int check = 0;

    GameBoard playingboard;
    initialize(playingboard);
    playingboard.printBoard();


    playingboard.getAllP1Moves();
    playingboard.printAllP1Moves();



    //doTestNextMove(playingboard);
    //playingboard.printPiece();
    //P1NextBoards p1(playingboard);
    //std::cout<<"DO MOVE P1()"<<std::endl;
    //p1.doMoveP1();
    //std::cout<<"PAST DO MOVE P1()"<<std::endl;

    /*std::cout<<"*** all possible boards: " <<p1.size()<<" ***"<<std::endl;
    for(int i=0; i<p1.size(); ++i) {
        GameBoard *gb = p1.getBoard(i);
        gb->printBoard();
    }*/


    //std::cout << "CHOOSE BOARD getNextSteps(idx)" << std::endl;
    //GameBoard *pgb = new GameBoard(playingboard);
    //pgb->printBoard();
    //std::cout<<"CREATED *pgb"<<std::endl;

    /*NextSteps *ns = p1.getNextSteps(1);
    for(int i=0; i<ns->steps.size(); ++i) {
        Step t = ns->steps[i];
        pgb->doMove(t.start, t.end);
    }*/
    //pgb->printBoard();
    //std::cout << "Your Possible Moves" << std::endl;
    //p1.displayAllMoves();
    //std::cout << "ALL MOVES DISPLAYED" << std::endl;

    //int choiceIdx = requestMoveInput();
    //GameBoard *gb = p1.getBoard(2);
    //playingboard.setBoard(gb->board);
    //playingboard.printBoard();
    //ns->print();
    return 0;

}
