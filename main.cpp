#include <iostream>
#include <string>
#include <sstream>
#include <utility>

#include "GameBoard.h"
#include "Player1.h"
#include "CheckerComposite.h"
#include "P1NextBoards.h"

void initialize(GameBoard &gb, int usernum) {
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
    gb.setBoard(testSquareJumpBoard);
    //gb.setBoard(testRegMoveBoard);
    gb.setPieces();
    gb.setHeuristic(usernum);


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
    int inputint;
    int maxsize = gb.size();

    while(true) {
        std::cout << "Please Enter Your Move: ";
        getline(std::cin, input);

        std::stringstream myStream(input);
        myStream >> inputint;
        if(inputint < maxsize)
            break;
        std::cout << "Invalid entry. Try again" << std::endl;
    }
    return inputint;
}

void doUserMove(int idx, GameBoard &gb) {
    gb.setBoard(gb.vectOfGb[idx]->board);
    gb.printBoard();
    gb.setPieces();
    gb.vectOfGb.clear();
}

int alphabeta(GameBoard *gb, int depth, int alpha, int beta, bool isMax, int userplayer, int *pruneNum, int *bestmoveidx) {
    GameBoard *ngb = new GameBoard();
    ngb->setBoard(gb->board);
    if(!gb->isRoot)
        ngb->printBoard();

    //std::cout << "ENTERED ALPHABETA" << std::endl;
    int cval;
    int v;
    if(userplayer == 1 && isMax == true) {
        ngb->getAllP2Moves(false, NULL);
    }
    else if (userplayer == 1 && isMax == false) { 
        ngb->getAllP1Moves(false, NULL);
    }
    else if(userplayer == 2 && isMax == true) {
        ngb->getAllP1Moves(false, NULL);
    }
    else {
        ngb->getAllP2Moves(false, NULL);
    }


    if (depth == 0 || ngb->isWin()) {
    	//std::cout << "RETURN HEURISTIC!" << std::endl;
        v = ngb->getHeuristic(userplayer);
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

void whoIsHuman (int *whoisHuman) {
    char input;
    while(true) {
        std::cout << "Player 1 or Player 2? [1 or 2]: ";
        std::cin.get(input);
        if(input == '1') {
            (*whoisHuman) = 1;
            break;
        }
        if(input == '2') {
            (*whoisHuman) = 2;
            break;
        }
        std::cout << "Invalid entry. Try again" << std::endl;
    }
}



int main () {

    int turncount = 0;
    int userIDX = 0;
    int userplayerNum = 1; //default

    int moveListIdx = 0;

    int num_of_prunes = 0;
    int *ptrNumOfPrunes = &num_of_prunes;
    int aiIdxBestMove = 0;
    int *ptraiidx = &aiIdxBestMove;

    int minimaxchoice;
    int depth_max = 3;

    GameBoard playingboard;
    playingboard.isRoot = true;
    GameBoard *playingboardptr = &playingboard;
    initialize(playingboard, userplayerNum);
    //whoIsHuman(&userplayerNum);

    std::cout << "              Turn: " << turncount;
    playingboard.printBoard();


    std::cout<<"=======PLAYER " << userplayerNum << " MOVES=========" << std::endl;
    playingboard.getMovesGeneral(userplayerNum, &moveListIdx);
    userIDX = requestMoveInput(playingboard.vectOfGb);
    std::cout << "userIDX: " << userIDX << std::endl;
    doUserMove(userIDX, playingboard);
    moveListIdx = 0;
    playingboard.getMovesGeneral(2, NULL);
    turncount++;
    std::cout << "              Turn: " << turncount << std::endl;

    //playingboard.getAllP2Moves(true, &moveListIdx);
    //playingboard.getAllP1Moves();
    //playingboard.printAllP1Moves();
    //userIDX = requestMoveInput(playingboard.vectOfGb);
    //doUserMove(userIDX, playingboard);

//IDDFS


    for (int i = 0; i <= depth_max; i++) {
        std::cout << "depth: " << i << std::endl;
        minimaxchoice = alphabeta(playingboardptr, i, -2000000, 2000000, true, userplayerNum, &num_of_prunes, &aiIdxBestMove);
    }
    std::cout << "vectsize: " << playingboard.vectOfGb.size() << "   minimax: " << minimaxchoice << "   prunes: " << num_of_prunes << "   index of best move: " << aiIdxBestMove<< std::endl;
    doUserMove(aiIdxBestMove, playingboard);
    std::cout << std::endl << std::endl << std::endl;

    //playingboard.setBoard(playingboard.vectOfGb[aiIdxBestMove]->board);
    

    //std::cout << "vectsize: " << playingboard.vectOfGb.size() << "   minimax: " << minimaxchoice << "   prunes: " << num_of_prunes << "   index of best move: " << aiIdxBestMove<< std::endl;
    //playingboard.printBoard();


//IDDFS END


    /*playingboard.vectOfGb.clear();
    std::cout << "size: " << playingboard.vectOfGb.size() << std::endl;

    std::cout << "vectsize: " << playingboard.vectOfGb.size() << "   minimax: " << minimaxchoice << "   prunes: " << num_of_prunes << "   index of best move: " << aiIdxBestMove<< std::endl;
*/
    /*std::cout<<"=======POSSIBLE MOVES=========" << std::endl;
    for(int i = 0; i < playingboard.vectOfGb.size(); i++) {
        playingboard.vectOfGb[i]->printBoard();
        std::cout << "HEURISTIC: " << playingboard.vectOfGb[i]->getHeuristic(userplayerNum) << std::endl;
    }*/

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
