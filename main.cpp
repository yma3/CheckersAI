#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <chrono>
#include <climits>

#include "GameBoard.h"

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
        {0, 0, 0, 0, 2, 0, 2, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    gb.setBoard(initialBoard);
    //gb.setBoard(testJumpBoard);
    //gb.setBoard(testSquareJumpBoard);
    //gb.setBoard(testRegMoveBoard);
    gb.setPieces();
    //gb.setHeuristic(usernum, );
}


int requestMoveInput(std::vector<GameBoard*> gb) {
    std::string input = "";
    int inputint;
    int maxsize = gb.size();

    while(true) {
        std::cout << "Please Enter Your Move: ";
        std::cin >> input;

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
    for(int j = 0; j < 8; j++) {
        if(gb.board[0][j] == 1) {
            gb.board[0][j] = 3;
        }
        if(gb.board[7][j] == 2) {
            gb.board[7][j] = 4;
        }
    }
    gb.setPieces();
    gb.hasAJump = false;
    gb.printBoard();
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

int alphabeta(GameBoard *gb, int depth, long alpha, long beta, bool isMax, int userplayer, int *pruneNum, int *bestmoveidx, int *foo, int whoseturn, int timeLimit, bool *timeOver, int enterdepth) {
    if(!(*timeOver)) {
        endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> secondsPassed = endTime-startTime;
        if(secondsPassed.count() > timeLimit) {
            (*timeOver) = true;
            return 0;
        }

        GameBoard *ngb = new GameBoard();
        ngb->setBoard(gb->board);
        ngb->setPieces();
        int cval;
        long v;
        if(userplayer == 1 && isMax == true) {
            ngb->getAllP2Moves(false, foo);
        }
        else if (userplayer == 1 && isMax == false) { 
            ngb->getAllP1Moves(false, foo);
        }
        else if(userplayer == 2 && isMax == true) {
            ngb->getAllP1Moves(false, foo);
        }
        else {
            ngb->getAllP2Moves(false, foo);
        }

        //std::cout << " Size: " << ngb->vectOfGb.size();

        if ((depth == 0) || (ngb->isWin(whoseturn) != 0)) {
        	//std::cout << "RETURN HEURISTIC!" << std::endl;
            v = ngb->setHeuristic(userplayer, depth, (gb->number_P1_pieces+gb->number_P2_pieces), enterdepth);
            delete ngb;
            return v;
        }
        //std::cout << "CURRENT DEPTH: " << depth << std::endl;
        //std::cout << "isMax: " << isMax << std::endl;
        if(isMax) {
        	//std::cout << "IS MAX!!!! " << userplayer;
            v = LONG_MIN;
            for(int i = 0; i < ngb->vectOfGb.size(); i++){
                cval = alphabeta(ngb->vectOfGb[i], depth - 1, alpha, beta, false, userplayer, pruneNum, bestmoveidx,foo, whoseturn, timeLimit, timeOver, enterdepth);
                delete ngb->vectOfGb[i];
                if(cval > v) {
                	v = cval;
                	if(gb->isRoot) {
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
            v = LONG_MAX;
            for(int i = 0; i < ngb->vectOfGb.size(); i++) {
            	//std::cout << "MIN! Depth: " << depth-1 << std::endl;
                cval = alphabeta(ngb->vectOfGb[i], depth - 1, alpha, beta, true, userplayer, pruneNum, bestmoveidx,foo, whoseturn, timeLimit, timeOver, enterdepth);
                delete ngb->vectOfGb[i];
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
    std::string input;
    while(true) {
        std::cout << "Player 1 or Player 2? [1 or 2]: ";
        std::cin >> input;
        if(input == "1") {
            (*whoisHuman) = 1;
            (*whoisAI) = 2;
            break;
        }
        if(input == "2") {
            (*whoisHuman) = 2;
            (*whoisAI) = 1;
            break;
        }
    std::cout << "Invalid entry. Try again" << std::endl;    }
}

bool humanvsAI() {
    std::string input;
    while(true) {
        std::cout << "Human vs AI? [y/n]: ";
        std::cin >> input;
        if(input == "y") {
            return true;
        }
        if(input == "n") {
            return false;
        }
        std::cout << "Invalid entry. Try again" << std::endl;
    }
}

void howMuchTime (int *howmuchtime) {
    std::string input;
    while(true) {
        std::cout << "How many seconds will the AI run?: ";
        std::cin >> input;
        if(stoi(input) > 0) {
            (*howmuchtime) = stoi(input);
            break;
        }
    std::cout << "Invalid entry. Try again" << std::endl;    }
}

bool readFromFile() {
    std::string input;
    while(true) {
        std::cout << "Read from a file? [y/n]: ";
        std::cin >> input;
        if(input == "y") {
            return true;
        }
        if(input == "n") {
            return false;
        }
        std::cout << "Invalid entry. Try again" << std::endl;
    }
}

bool fromAFile(unsigned char board[][8], int *whoseturn, int *timeLimit) {

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            board[i][j] = 0;
        }
    }

    std::string inputfilename = "";
    std::cout << "Input file name: " << std::endl;
    std::cin >> inputfilename;
    std::ifstream inputfile;
    inputfile.open(inputfilename);
    if(!inputfile) {
        std::cout<<"No file" << std::endl;
    }
    int inputvalue;
    for(int i = 0; i < 8; i++) {
        for(int j = (i+1)%2; j < 8; j+=2) {
            inputfile >> inputvalue;
            board[i][j] = inputvalue;
        }
    }
    inputfile >> (*whoseturn);
    inputfile >> (*timeLimit);
    inputfile.close();
    return true;
}

void clearVectOfGb(GameBoard &gb) {
    for(int i = 0; i < gb.vectOfGb.size(); i++) {
        delete gb.vectOfGb[i];
    }
    gb.vectOfGb.clear();
}

int main () {

    int turncount = 0;
    int userIDX = 0;

    int userplayerNum = 2; //default
    int aiNumber = 1;
    int whoseturn = 1;

    int moveListIdx = 0;

    int num_of_prunes = 0;
    int *ptrNumOfPrunes = &num_of_prunes;
    int aiIdxBestMove = 0;
    int *ptraiidx = &aiIdxBestMove;

    int minimaxchoice;

    bool timeOver = false;
    double secondsPassed;
    int timeLimit = 2;
    int depth_max = 10000;

    GameBoard playingboard;
    playingboard.isRoot = true;
    GameBoard *playingboardptr = &playingboard;
    initialize(playingboard, userplayerNum);

    bool fromfile = readFromFile();
    if(fromfile) {
        fromAFile(playingboard.board, &whoseturn, &timeLimit);
        playingboard.setBoard(playingboard.board);
        playingboard.setPieces();
    }


    //=========================== H U M A N    V S     A I ====================================
    if(humanvsAI()) {
        std::cout << "Playing Human vs AI" << std::endl;
        whoIsHuman(&userplayerNum, &aiNumber);
        if(!fromfile) {
            howMuchTime(&timeLimit);
        }
        playingboard.printBoard();

        if(userplayerNum == 2) {
            std::cout << "            Turn: " << turncount++ << std::endl;
            std::cout<<"=======PLAYER " << aiNumber << " MOVES=========" << std::endl;
            startTime = std::chrono::high_resolution_clock::now();
            timeOver = false;
            for (int i = 1; i < depth_max; i++) {
                if(!timeOver) {
                    minimaxchoice = alphabeta(playingboardptr, i, LONG_MIN, LONG_MAX, true, userplayerNum, &num_of_prunes, &aiIdxBestMove, &moveListIdx, whoseturn, timeLimit, &timeOver, i);
                }
                else {
                    std::cout << "Reached depth: " << i-1 << std::endl;
                    endTime = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> secondsPassed = endTime-startTime;
                    std::cout << "seconds passed: " << secondsPassed.count() << std::endl;
                    break;
                }
            }
            if(!timeOver) {
                std::cout << "Reached depth: " << depth_max << std::endl;
                endTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> secondsPassed = endTime-startTime;
                std::cout << "seconds passed: " << secondsPassed.count() << std::endl;
            }
            clearVectOfGb(playingboard);
            num_of_prunes = 0;
            moveListIdx = 0;
            playingboard.getMovesGeneralDontDisplayMoves(aiNumber, &moveListIdx);
            moveListIdx = 0;
            //std::cout << "vectsize: " << playingboard.vectOfGb.size() << "   minimax: " << minimaxchoice << "   prunes: " << num_of_prunes << "   index of best move: " << aiIdxBestMove<< std::endl;
            doUserMove(aiIdxBestMove, playingboard, &whoseturn);
            clearVectOfGb(playingboard);
            std::cout << std::endl << std::endl;
        }
        while(true){
            if(whoseturn == userplayerNum) {
                std::cout << "            Turn: " << turncount++ << std::endl;
                std::cout<<"=======PLAYER " << userplayerNum << " MOVES=========" << std::endl;
                playingboard.getMovesGeneral(userplayerNum, &moveListIdx);
                userIDX = requestMoveInput(playingboard.vectOfGb);
                moveListIdx = 0;
                doUserMove(userIDX, playingboard, &whoseturn);
                moveListIdx = 0;
                turncount++;
            }

        //IDDFS
            else{
                std::cout << "            Turn: " << turncount++ << std::endl;
                std::cout<<"=======PLAYER " << aiNumber << " MOVES=========" << std::endl;
                
                playingboard.getMovesGeneral(aiNumber, &moveListIdx);
                if(playingboard.vectOfGb.size()==1) {
                    std::cout << "AI picked the only move." << std::endl;
                    doUserMove(0, playingboard, &whoseturn);
                    moveListIdx = 0;
                }
                else{
                    clearVectOfGb(playingboard);
                    startTime = std::chrono::high_resolution_clock::now();
                    timeOver = false;
                    for (int i = 1; i < depth_max; i++) {
                        if(!timeOver) {
                            minimaxchoice = alphabeta(playingboardptr, i, LONG_MIN, LONG_MAX, true, userplayerNum, &num_of_prunes, &aiIdxBestMove, &moveListIdx, whoseturn, timeLimit, &timeOver, i);
                        }
                        else {
                            std::cout << "Reached depth: " << i-1 << std::endl;
                            endTime = std::chrono::high_resolution_clock::now();
                            std::chrono::duration<double> secondsPassed = endTime-startTime;
                            std::cout << "seconds passed: " << secondsPassed.count() << std::endl;
                            break;
                        }
                    }
                    if(!timeOver) {
                        std::cout << "Reached depth: " << depth_max << std::endl;
                        endTime = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double> secondsPassed = endTime-startTime;
                        std::cout << "seconds passed: " << secondsPassed.count() << std::endl;
                    }
                    clearVectOfGb(playingboard);
                    moveListIdx = 0;
                    playingboard.getMovesGeneralDontDisplayMoves(aiNumber, &moveListIdx);
                    moveListIdx = 0;
                    //std::cout << "vectsize: " << playingboard.vectOfGb.size() << "   minimax: " << minimaxchoice << "   prunes: " << num_of_prunes << "   index of best move: " << aiIdxBestMove<< std::endl;
                    doUserMove(aiIdxBestMove, playingboard, &whoseturn);
                }
            }
            std::cout << std::endl << std::endl;
            if(playingboard.isWin(whoseturn) != 0) {
                std::cout << "GAME OVER BY!" << std::endl;
                switch(playingboard.isWin(whoseturn)) {
                    case 1: std::cout << "Player " << whoseturn << " has no more moves!" << std::endl; break;
                    case 2: std::cout << "Player 2 has no more pieces!" << std::endl; break;
                    case 3: std::cout<< " Player 1 has no more pieces!" << std::endl; break;
                }
                break;
            }
            clearVectOfGb(playingboard);
        }
    }

    //=========================== AI    V S     A I ====================================
    else {
        std::cout << "Playing AI vs AI" << std::endl;
        if(!fromfile) {
            howMuchTime(&timeLimit);
        }
        playingboard.printBoard();
        int ai2bestchoice = 0;
        while(true){
            if(whoseturn == 1) {
                std::cout << "            Turn: " << turncount++ << std::endl;
                std::cout<<"=======PLAYER 1 MOVES=========" << std::endl;
                playingboard.getMovesGeneral(1, &moveListIdx);
                if(playingboard.vectOfGb.size()==1) {
                    playingboard.printAllP1Moves();
                    std::cout << "AI picked the only move." << std::endl;
                    doUserMove(0, playingboard, &whoseturn);
                    moveListIdx = 0;
                }
                else{
                    clearVectOfGb(playingboard);
                    startTime = std::chrono::high_resolution_clock::now();
                    timeOver = false;
                    for (int i = 1; i < depth_max; i++) {
                        if(!timeOver) {
                            minimaxchoice = alphabeta(playingboardptr, i, LONG_MIN, LONG_MAX, true, 2, &num_of_prunes, &aiIdxBestMove, &moveListIdx, whoseturn, timeLimit, &timeOver, i);
                        }
                        else {
                            std::cout << "Reached depth: " << i-1 << std::endl;
                            endTime = std::chrono::high_resolution_clock::now();
                            std::chrono::duration<double> secondsPassed = endTime-startTime;
                            std::cout << "seconds passed: " << secondsPassed.count() << std::endl;
                            break;
                        }
                    }
                    clearVectOfGb(playingboard);
                    moveListIdx = 0;
                    playingboard.getMovesGeneralDontDisplayMoves(1, &moveListIdx);
                    doUserMove(aiIdxBestMove, playingboard, &whoseturn);
                }
                std::cout << std::endl;
                moveListIdx = 0;
            }

            else{
                std::cout << "            Turn: " << turncount++ << std::endl;
                std::cout<<"=======PLAYER 2 MOVES=========" << std::endl;
                playingboard.getMovesGeneral(2, &moveListIdx);
                if(playingboard.vectOfGb.size()==1) {
                    playingboard.printAllP1Moves();
                    std::cout << "AI picked the only move." << std::endl;
                    doUserMove(0, playingboard, &whoseturn);
                    moveListIdx = 0;
                }
                else{
                    startTime = std::chrono::high_resolution_clock::now();
                    timeOver = false;
                    for (int i = 1; i < depth_max; i++) {
                        if(!timeOver) {
                            minimaxchoice = alphabeta(playingboardptr, i, LONG_MIN, LONG_MAX, true, 1, &num_of_prunes, &aiIdxBestMove, &moveListIdx, whoseturn, timeLimit, &timeOver, i);
                        }
                        else {
                            std::cout << "Reached depth: " << i-1 << std::endl;
                            endTime = std::chrono::high_resolution_clock::now();
                            std::chrono::duration<double> secondsPassed = endTime-startTime;
                            std::cout << "seconds passed: " << secondsPassed.count() << std::endl;
                            break;
                        }
                    }
                    clearVectOfGb(playingboard);
                    moveListIdx = 0;
                    playingboard.getMovesGeneralDontDisplayMoves(2, &moveListIdx);
                    doUserMove(aiIdxBestMove, playingboard, &whoseturn);
                }
                std::cout << std::endl;
                moveListIdx = 0;
            }

            if(playingboard.isWin(whoseturn) != 0) {
                std::cout << "=> GAME OVER! <=" << std::endl;
                switch(playingboard.isWin(whoseturn)) {
                    case 1: std::cout << "Player " << whoseturn << " has no more moves!" << std::endl; break;
                    case 2: std::cout << "Player 2 has no more pieces!" << std::endl; break;
                    case 3: std::cout<< " Player 1 has no more pieces!" << std::endl; break;
                }
                break;
            }
            clearVectOfGb(playingboard);
        }
    }
    return 0;
}
