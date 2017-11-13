#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <chrono>

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
        {0, 0, 0, 4, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    gb.setBoard(initialBoard);
    //gb.setBoard(testJumpBoard);
    //gb.setBoard(testSquareJumpBoard);
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

void doUserMove(int idx, GameBoard &gb, int *whoseturn) {
    gb.setBoard(gb.vectOfGb[idx]->board);
    gb.setPieces();
    gb.hasAJump = false;
    gb.printBoard();
    //gb.setPieces();
    for(int i = 0; i < gb.vectOfGb.size(); i++) {
        delete gb.vectOfGb[i];
    }
    gb.vectOfGb.clear();
    if((*whoseturn)==1)
        (*whoseturn) = 2;
    else if((*whoseturn)==2)
        (*whoseturn) = 1;

}

std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

int alphabeta(GameBoard *gb, int depth, int alpha, int beta, bool isMax, int userplayer, int *pruneNum, int *bestmoveidx, int *foo, int whoseturn, int timeLimit, bool *timeOver) {
    if(!(*timeOver)) {
        endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> secondsPassed = endTime-startTime;
        if(secondsPassed.count() > timeLimit) {
            std::cout << "seconds passed: " << secondsPassed.count() << std::endl;
            (*timeOver) = true;
            return 0;
        }

        GameBoard *ngb = new GameBoard();
        ngb->setBoard(gb->board);
        ngb->setPieces();
        if(!gb->isRoot){
            //ngb->printBoard();
        }
        //std::cout << std::endl;
        //std::cout << "ENTERED ALPHABETA" << std::endl;
        int cval;
        int v;
        if(userplayer == 1 && isMax == true) {
            ngb->getAllP2Moves(false, foo);
            //std::cout << "1~~";
            //ngb->printAllP1Moves();
        }
        else if (userplayer == 1 && isMax == false) { 
            ngb->getAllP1Moves(false, foo);
           // std::cout << "2~~";
            //ngb->printAllP1Moves();
        }
        else if(userplayer == 2 && isMax == true) {
            ngb->getAllP1Moves(false, foo);
            //std::cout << "3~~";
            //ngb->printAllP1Moves();
        }
        else {
            ngb->getAllP2Moves(false, foo);
          //  std::cout << "4~~";
            //ngb->printAllP1Moves();
        }

        //std::cout << " Size: " << ngb->vectOfGb.size();

        if ((depth == 0) || (ngb->isWin(whoseturn) != 0)) {
        	//std::cout << "RETURN HEURISTIC!" << std::endl;
            v = ngb->getHeuristic(userplayer);
            delete ngb;
            return v;
        }
        //std::cout << "CURRENT DEPTH: " << depth << std::endl;
        //std::cout << "isMax: " << isMax << std::endl;
        if(isMax) {
        	//std::cout << "IS MAX!!!! " << userplayer;
            v = -2000000;
        	//std::cout << "Size: " << ngb->vectOfGb.size() << std::endl;
            for(int i = 0; i < ngb->vectOfGb.size(); i++){
            //	std::cout << " i: " << i;
                cval = alphabeta(ngb->vectOfGb[i], depth - 1, alpha, beta, false, userplayer, pruneNum, bestmoveidx,foo, whoseturn, timeLimit, timeOver);
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
            delete ngb;
            return v;
        }

        else {
            //std::cout << "IS MIN!!!! " << userplayer;
            v = 2000000;
            for(int i = 0; i < ngb->vectOfGb.size(); i++) {
            	//std::cout << "MIN! Depth: " << depth-1 << std::endl;
                cval = alphabeta(ngb->vectOfGb[i], depth - 1, alpha, beta, true, userplayer, pruneNum, bestmoveidx,foo, whoseturn, timeLimit, timeOver);
                if(cval < v) {
                	v = cval;
                }   
                beta = std::min(beta, v);
                if (beta <= alpha) {
                	(*pruneNum)++;
                    break;
                }
                delete ngb;
            return v;
        	}
    	}
    }
	return 0;	
}

void whoIsHuman (int *whoisHuman, int *whoisAI) {
    char input;
    while(true) {
        std::cout << "Player 1 or Player 2? [1 or 2]: ";
        std::cin.get(input);
        if(input == '1') {
            (*whoisHuman) = 1;
            (*whoisAI) = 2;
            break;
        }
        if(input == '2') {
            (*whoisHuman) = 2;
            (*whoisAI) = 1;
            break;
        }
        std::cout << "Invalid entry. Try again" << std::endl;
    }
}

bool humanvsAI() {
    char input;
    while(true) {
        std::cout << "Human vs AI? [y/n]: ";
        std::cin.get(input);
        if(input == 'y') {
            return true;
        }
        if(input == 'n') {
            return false;
        }
        std::cout << "Invalid entry. Try again" << std::endl;
    }
}



int main () {

    int turncount = 0;
    int userIDX = 0;

    //bool humanvsAI = true;

    int userplayerNum = 2; //default
    int aiNumber = 1;
    int whoseturn = 1;

    int moveListIdx = 0;

    int num_of_prunes = 0;
    int *ptrNumOfPrunes = &num_of_prunes;
    int aiIdxBestMove = 0;
    int *ptraiidx = &aiIdxBestMove;

    int minimaxchoice;
    //time_t startTime;
    //time_t endTime;
    bool timeOver = false;
    double secondsPassed;
    int timeLimit = 5;
    int depth_max = 15;

    GameBoard playingboard;
    playingboard.isRoot = true;
    GameBoard *playingboardptr = &playingboard;
    initialize(playingboard, userplayerNum);
    //whoIsHuman(&userplayerNum);




    //=========================== H U M A N    V S     A I ====================================
    if(humanvsAI()) {

        std::cout << "Playing Human vs AI" << std::endl;
        whoIsHuman(&userplayerNum, &aiNumber);

        std::cout << "              Turn: " << turncount;
        playingboard.printBoard();

        if(userplayerNum == 2) {
            startTime = std::chrono::high_resolution_clock::now();
            timeOver = false;
            for (int i = 1; i < depth_max; i++) {
                if(!timeOver) {
                    minimaxchoice = alphabeta(playingboardptr, i, -2000000, 2000000, true, userplayerNum, &num_of_prunes, &aiIdxBestMove, &moveListIdx, whoseturn, timeLimit, &timeOver);
                }
            }
            num_of_prunes = 0;
            moveListIdx = 0;
            playingboard.getMovesGeneral(aiNumber, &moveListIdx);
            moveListIdx = 0;
            //std::cout << "size: " << playingboard.vectOfGb.size() << std::endl;
            std::cout << "vectsize: " << playingboard.vectOfGb.size() << "   minimax: " << minimaxchoice << "   prunes: " << num_of_prunes << "   index of best move: " << aiIdxBestMove<< std::endl;
            doUserMove(aiIdxBestMove, playingboard, &whoseturn);
            for(int i = 0; i < playingboard.vectOfGb.size(); i++) {
                delete playingboard.vectOfGb[i];
            }
            playingboard.vectOfGb.clear();
            std::cout << std::endl << std::endl << std::endl;
            //timeOver = false;
        }
        while(true){
            std::cout<<"=======PLAYER " << userplayerNum << " MOVES=========" << std::endl;
            playingboard.getMovesGeneral(userplayerNum, &moveListIdx);
            userIDX = requestMoveInput(playingboard.vectOfGb);
            std::cout << "userIDX: " << userIDX << std::endl;
            //playingboard.vectOfGb[userIDX]->printBoard();
            doUserMove(userIDX, playingboard, &whoseturn);
            moveListIdx = 0;
            turncount++;
            std::cout << "              Turn: " << turncount << std::endl;

            //playingboard.getAllP2Moves(true, &moveListIdx);
            //playingboard.getAllP1Moves();
            //playingboard.printAllP1Moves();
            //userIDX = requestMoveInput(playingboard.vectOfGb);
            //doUserMove(userIDX, playingboard);

        //IDDFS
            startTime = std::chrono::high_resolution_clock::now();
            timeOver = false;
            for (int i = 1; i < depth_max; i++) {
                if(!timeOver) {
                    minimaxchoice = alphabeta(playingboardptr, i, -2000000, 2000000, true, userplayerNum, &num_of_prunes, &aiIdxBestMove, &moveListIdx, whoseturn, timeLimit, &timeOver);
                }
            }
            num_of_prunes = 0;
            moveListIdx = 0;
            playingboard.getMovesGeneral(aiNumber, &moveListIdx);
            moveListIdx = 0;
            //std::cout << "size: " << playingboard.vectOfGb.size() << std::endl;
            std::cout << "vectsize: " << playingboard.vectOfGb.size() << "   minimax: " << minimaxchoice << "   prunes: " << num_of_prunes << "   index of best move: " << aiIdxBestMove<< std::endl;
            doUserMove(aiIdxBestMove, playingboard, &whoseturn);
            for(int i = 0; i < playingboard.vectOfGb.size(); i++) {
                delete playingboard.vectOfGb[i];
            }
            playingboard.vectOfGb.clear();
            std::cout << std::endl << std::endl << std::endl;


            if(playingboard.isWin(whoseturn) != 0) {
                std::cout << "GAME OVER BY: " << playingboard.isWin(whoseturn) << std::endl;
                break;
            }
        }
    }

    else {
        int ai2bestchoice = 0;
        while(true){
            std::cout << "              Turn: " << turncount++ << std::endl;
            std::cout<<"========AI PLAYER 1==========" << std::endl;

            //Player 1 Moves
            for (int i = 1; i < depth_max; i++) {
                //std::cout << std::endl << "depth: " << i << std::endl;
                minimaxchoice = alphabeta(playingboardptr, i, -2000000, 2000000, true, 2, &num_of_prunes, &aiIdxBestMove, &moveListIdx, whoseturn, timeLimit, &timeOver);
            }
            timeOver = false;
            playingboard.getMovesGeneral(1, &moveListIdx);
            doUserMove(aiIdxBestMove, playingboard, &whoseturn);
            std::cout << std::endl;
            moveListIdx = 0;


            std::cout << "              Turn: " << turncount++ << std::endl;
            std::cout<<"========AI PLAYER 2==========" << std::endl;
            //Player 2 Moves
            for (int i = 1; i < depth_max; i++) {
                //std::cout << std::endl << "depth: " << i << std::endl;
                minimaxchoice = alphabeta(playingboardptr, i, -2000000, 2000000, true, 1, &num_of_prunes, &aiIdxBestMove, &moveListIdx, whoseturn, timeLimit, &timeOver);
            }
            timeOver = false;
            playingboard.getMovesGeneral(2, &moveListIdx);
            doUserMove(aiIdxBestMove, playingboard, &whoseturn);
            std::cout << std::endl;
            moveListIdx = 0;

            if(playingboard.isWin(whoseturn) != 0) {
                std::cout << "GAME OVER BY: " << playingboard.isWin(whoseturn) << std::endl;
                break;
            }

            std::cin.get();
        }
    }



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
