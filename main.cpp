#include <iostream>
#include <string>
#include <sstream>
#include <utility>

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
    unsigned char testRegMoveBoard[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 0, 3, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    //gb.setBoard(initialBoard);
    //gb.setBoard(testJumpBoard);
    //gb.setBoard(testSquareJumpBoard);
    gb.setBoard(testRegMoveBoard);
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

int requestMoveInput(std::vector<GameBoard*> gb) {
    std::string input = "";
    int maxsize = gb.size();

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

void doUserMove(int idx, GameBoard &gb) {
    gb.setBoard(gb.vectOfGb[idx]->board);
    gb.printBoard();
    gb.vectOfGb.clear();
}

int alphabeta(GameBoard *gb, int depth, int alpha, int beta, bool isMax, int userplayer, int *pruneNum, int *bestmoveidx) {
    GameBoard *ngb = new GameBoard();
    ngb->setBoard(gb->board);
    //ngb->printBoard();

    //std::cout << "ENTERED ALPHABETA" << std::endl;
    int cval;
    int v;
    if(userplayer == 1) {
        ngb->getAllP2Moves();
        //std::cout << "GET P2 MOVES! Size of Vect: " << ngb->vectOfGb.size() << std::endl;
    } else {
        ngb->getAllP1Moves();
        //std::cout << "GET P1 MOVES! Size of Vect: " << ngb->vectOfGb.size() << std::endl;
    }

    if (depth == 0 || ngb->isWin()) {
    	//std::cout << "RETURN HEURISTIC!" << std::endl;
        v = ngb->getHeuristic();
        return v;
    }
    //std::cout << "CURRENT DEPTH: " << depth << std::endl;
    //std::cout << "isMax: " << isMax << std::endl;
    if(isMax) {
    	//std::cout << "IS MAX!!!!" << userplayer << std::endl;
        v = -2000000;
    	//std::cout << "Size: " << ngb->vectOfGb.size() << std::endl;
        for(int i = 0; i < ngb->vectOfGb.size(); i++){
        	//std::cout << "i: " << i << std::endl;
            cval = alphabeta(ngb->vectOfGb[i], depth - 1, alpha, beta, false, userplayer, pruneNum, bestmoveidx);
            if(cval > v) {
            	v = cval;
            	if(gb->isRoot) {
            		//std::cout << "SETTING VALUE TO i: " << i << std::endl;
            		(*bestmoveidx) = i;
            	}
            }   
            alpha = std::max(alpha, v);
            if (beta <= alpha) {
            	(*pruneNum)++;
                break;
            }
        }
        return v;
    }

    else {
        v = 2000000;
        for(int i = 0; i < ngb->vectOfGb.size(); i++) {
        	//std::cout << "MIN! Depth: " << depth-1 << std::endl;
            cval = alphabeta(ngb->vectOfGb[i], depth - 1, alpha, beta, true, userplayer, pruneNum, bestmoveidx);
            if(cval < v) {
            	v = cval;
            }   
            beta = std::min(beta, v);
            if (beta <= alpha) {
            	(*pruneNum)++;
                break;
            }
        return v;
    	}
	}
	return v;	
}



int main () {

    int check = 0;
    int userIDX = 0;
    int userplayerNum = 1; //default

    int num_of_prunes = 0;
    int *ptrNumOfPrunes = &num_of_prunes;
    int aiIdxBestMove = 0;
    int *ptraiidx = &aiIdxBestMove;

    int minimaxchoice;
    int depth_max = 2;

    GameBoard playingboard;
    playingboard.isRoot = true;
    GameBoard *playingboardptr = &playingboard;
    initialize(playingboard);
    playingboard.printBoard();


    std::cout<<"=======PLAYER 1 MOVES=========" << std::endl;
    //playingboard.getAllP1Moves();
    //playingboard.printAllP1Moves();
    //userIDX = requestMoveInput(playingboard.vectOfGb);
    //doUserMove(userIDX, playingboard);
    /*std::cout << "Size of vect: " << playingboard.vectOfGb.size() << std::endl;

    for (int i = 1; i <= depth_max; i++) {
        std::cout << "depth: " << i << std::endl;
        minimaxchoice = alphabeta(playingboardptr, i, -2000000, 2000000, true, userplayerNum, ptrNumOfPrunes, ptraiidx);
    }
    

    std::cout << "vectsize: " << playingboard.vectOfGb.size() << "   minimax: " << minimaxchoice << "   prunes: " << num_of_prunes << "   index of best move: " << aiIdxBestMove<< std::endl;
	std::cout << std::endl << std::endl << std::endl;

    playingboard.vectOfGb.clear();*/
    std::cout << "size: " << playingboard.vectOfGb.size() << std::endl;
    if(userplayerNum == 1)
        playingboard.getAllP2Moves();
    else
        playingboard.getAllP1Moves();
    std::cout << "vectsize: " << playingboard.vectOfGb.size() << "   minimax: " << minimaxchoice << "   prunes: " << num_of_prunes << "   index of best move: " << aiIdxBestMove<< std::endl;

    for(int i = 0; i < playingboard.vectOfGb.size(); i++) {
        playingboard.vectOfGb[i]->printBoard();
    }

	//playingboard.setBoard(playingboard.vectOfGb[aiIdxBestMove]->board);
	//playingboard.printBoard();
    

    //playingboard.printAllP1Moves();
    //playingboard.printBoard();
    //std::cout << playingboardptr << std::endl;
    //std::cout<<"=======PLAYER 2 MOVES=========" << std::endl;
    //playingboard.getAllP2Moves();


    //playingboard.printP1MoveList();
    //std::cout << playingboard.hasAJump << std::endl;


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
