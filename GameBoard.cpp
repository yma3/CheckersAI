//
// Created by New on 11/4/2017.
//
#include <iostream>
#include <algorithm>
#include "GameBoard.h"
#include <cstdlib>
#include <cmath>
#include <climits>

void GameBoard::setBoard(unsigned char myboard[][8]) {
    for(int i=0; i<8; ++i) {
        for(int j=0; j<8; ++j) {
            board[i][j] = myboard[i][j];
        }
    }
}

void GameBoard::setPieces() {
    number_P1_pieces = 0;
    number_P2_pieces = 0;
    for(int i=0; i<8; ++i) {
        for(int j=0; j<8; ++j) {
            int k = board[i][j];
            switch(k) {
            case 1:
            case 3:
                P1_pieces[number_P1_pieces].x = i;
                P1_pieces[number_P1_pieces++].y = j;
                break;
            case 2:
            case 4:
                P2_pieces[number_P2_pieces].x = i;
                P2_pieces[number_P2_pieces++].y = j;
                break;
            }
        }
    }
}

void GameBoard::printPiece() {
    std::cout << "=== MAX PIECES ===" << std::endl;
    for(int i = 0; i<number_P1_pieces; ++i) {
        XY cc = P1_pieces[i];
        std::cout<<(int)cc.x<<", " << (int)cc.y <<std::endl;
    }
    std::cout << "=== MIN PIECES ===" << std::endl;
    for(int i = 0; i<number_P2_pieces; ++i) {
        XY cc = P2_pieces[i];
        std::cout<< (int)cc.x<<", " << (int)cc.y <<std::endl;
    }
}

void GameBoard::printBoard() {
    std::cout << std::endl << "   =================================";
    std::cout << std::endl << "   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |";

    for (int i = 0; i <8; i++) {
        std::cout << std::endl << "---+---+---+---+---+---+---+---+---+"<< std::endl;
        std::cout << " " << i << " ";
        for(int j = 0; j < 8; j++) {
            int boardval = board[i][j];
            std::cout << "|";
            if((i+j)%2 == 1) {
                std::cout << "\033[0;96;40m";
            }
            else {
                std::cout << "\033[0;97;107m";
            }
            if( (!boardval == 0)) {
                if(boardval == 1)
                    std::cout << "\033[0;96;40m " << "o" << " " << "\033[0m";
                else if (boardval == 2)
                    std::cout << "\033[0;91;40m " << "o" << " " << "\033[0m";
                else if (boardval == 3)
                    std::cout << "\033[0;96;40m " << "8" << " " << "\033[0m";
                else if (boardval == 4)
                    std::cout << "\033[0;91;40m " << "8" << " " << "\033[0m";   
            }
            else {
                std::cout << "  " << " " << "\033[0m";
            }
            if(j == 7) {
                std::cout << "|";
            }
        }
        if(i == 7) {
            std::cout << std::endl << "---+---+---+---+---+---+---+---+---+"<< std::endl;
        }
    }
    printInfo();
}

void GameBoard::printInfo() {
    std::cout << "===================================="<< std::endl;
    std::cout << " Player 1:  " << "\033[0;96;40m  " << "o" << " " << "\033[0m" << "     ";
    std::cout << " Player 2: " << "\033[0;91;40m " << "o" << " " << "\033[0m" << std::endl;
    std::cout << " Player 1 K: " << "\033[0;96;40m " << "8" << " " << "\033[0m" << "   ";
    std::cout << " Player 2 K: " << "\033[0;91;40m " << "8" << " " << "\033[0m" <<std::endl;
    std::cout << "===================================="<< std::endl;
}


void GameBoard::flipBoard() {
    unsigned char temp[8][8];
    for(int i=0; i<8; ++i) {
        for(int j=0; j<8; ++j) {
            temp[i][j] = board[7-i][7-j];
        }
    }

    for(int i=0; i<8; ++i) {
        for(int j=0; j<8; ++j) {
            board[i][j] = temp[i][j];
        }
    }
}


long GameBoard::setHeuristic(int usernum, int currdepth, int currpiece, int startingdepth) {
    if(usernum == 1) {
        if(number_P1_pieces == 0)
            return LONG_MAX - 1 - ((currdepth - startingdepth)*10000) - (rand()%100);
        else if(number_P2_pieces == 0)
            return LONG_MIN + 1 + ((currdepth - startingdepth)*10000) + (rand()%100);
    }
    else {
        if(number_P2_pieces == 0)
            return LONG_MAX - 1 - ((currdepth - startingdepth)*10000) - (rand()%100);
        if(number_P1_pieces == 0)
            return  LONG_MIN + 1 + ((currdepth - startingdepth)*10000) + (rand()%100);
    }
    int pieceval = pieceValue(usernum);
    int avgtoking = (kingDist(usernum%2+1)-kingDist(usernum))*99/7;
    int piecesleft = lessPieces(currpiece, usernum);
    int locweight = positioningWeight(usernum);
    int randomportion = rand()%100;

    return (pieceval*10000000)+(avgtoking*100000)+(piecesleft*1000)+(locweight*10)+randomportion;
}

int GameBoard::pieceValue(int usernum) {
    int player1score;
    int player2score;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            unsigned char pieceVal = board[i][j];
            switch(pieceVal) {
                case 0: break;
                case 1: player2score += 5; break;
                case 2: player1score += 5; break;
                case 3: player2score += 10; break;
                case 4: player1score += 10; break;
            }
        }
    }
    if((usernum) == 1)
        return player1score - player2score;
    else
        return player2score - player1score;
}

int GameBoard::kingDist(int usernum) {
    int p1toKVal = 0;
    int p2toKVal = 0;
    int p1regnum = 0;
    int p2regnum = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            unsigned char pieceVal = board[i][j];
            switch(pieceVal) {
                case 0: break;
                case 1: p1toKVal += (7-i); p1regnum++; break;
                case 2: p2toKVal += i; p2regnum++; break;
            }
        }
    }
    if((usernum) == 1) {
        if(p1regnum == 0) {
            return 0;
        }
        else if (p2regnum == 0) {
            return p1toKVal/p1regnum;
        }
        else {
            return ((p1toKVal/p1regnum) - (p2toKVal/p2regnum))*99/7;
        }
    }
    else {
        if(p2regnum == 0) {
            return 0;
        }
        else if (p1regnum == 0) {
            return p2toKVal/p2regnum;
        }
        else {
            return ((p2toKVal/p2regnum) - (p1toKVal/p1regnum))*99/7;
        }
    }    
}

int GameBoard::lessPieces(int currentnumofpieces, int usernum) {
    if(usernum == 1) {
        if(number_P1_pieces > number_P2_pieces)
            return (24-currentnumofpieces)*99/24;
        else
            return (currentnumofpieces)*99/24;
    }
    else {
        if(number_P2_pieces > number_P1_pieces)
            return (24-currentnumofpieces)*99/24;
        else
            return (currentnumofpieces)*99/24;
    }
}

int GameBoard::positioningWeight(int usernum) {
    int p1edgeweight = 0;
    int p2edgeweight = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            unsigned char pieceval = board[i][j];
            switch(pieceval) {
                case 0: break;
                case 1: 
                    if(i == 0 || i == 7 || j == 0 || j == 7)
                        p1edgeweight += 4;
                    if( (i==1&&j>0) || (i==6&&j<7) ) 
                        p1edgeweight += 3;
                    if ((i==2&&j>1&&j<6) || (i==5&&j>1&&j<6))
                        p1edgeweight += 2;
                    if((i==4&&j==3) || (i==3&&j==4) )
                        p1edgeweight += 1;
                    break;
                case 2: 
                    if(i == 0 || i == 7 || j == 0 || j == 7)
                        p2edgeweight += 4;
                    if( (i==1&&j>0) || (i==6&&j<7) ) 
                        p2edgeweight += 3;
                    if ((i==2&&j>1&&j<6) || (i==5&&j>1&&j<6))
                        p2edgeweight += 2;
                    if((i==4&&j==3) || (i==3&&j==4) )
                        p2edgeweight += 1;
                    break;
                case 3: 
                    if(i == 0 || i == 7 || j == 0 || j == 7)
                        p1edgeweight += 6;
                    if( (i==1&&j>0) || (i==6&&j<7) ) 
                        p1edgeweight += 5;
                    if ((i==2&&j>1&&j<6) || (i==5&&j>1&&j<6))
                        p1edgeweight += 4;
                    if((i==4&&j==3) || (i==3&&j==4) )
                        p1edgeweight += 3;
                    break;
                case 4: 
                    if(i == 0 || i == 7 || j == 0 || j == 7)
                        p2edgeweight += 6;
                    if( (i==1&&j>0) || (i==6&&j<7) ) 
                        p2edgeweight += 5;
                    if ((i==2&&j>1&&j<6) || (i==5&&j>1&&j<6))
                        p2edgeweight += 4;
                    if((i==4&&j==3) || (i==3&&j==4) )
                        p2edgeweight += 3;
                    break;
            }
        }
    }
    if((usernum) == 1)
        return p1edgeweight - p2edgeweight;
    else
        return p2edgeweight - p1edgeweight;
}


void GameBoard::doMove(XY start, XY end) {
    int dx = end.x - start.x;
    if(dx == 2 || dx == -2) {
        board[(start.x+end.x)/2][(start.y+end.y)/2] = 0;
    }
    board[end.x][end.y] = board[start.x][start.y];
    board[start.x][start.y] = 0;
}




bool GameBoard::getMoves(XY cc, unsigned char board[][8], std::vector<GameBoard*> &myvectofgb, XY list[], int pathlength, bool requestMove, int *moveListIdx, bool player1) {
    GameBoard *gb = new GameBoard();
    gb->setBoard(board);

    if(isRoot) {
        pathlength = 0;
    }
    list[pathlength] = cc;
    int currentlength = pathlength;

    bool isLastMove = true;
    int currval = board[cc.x][cc.y];

    if(player1) {
        REGULAR = 2; KINGVAL = 4;
    }
    else {
        REGULAR = 1; KINGVAL = 3;
    }
    //TOP LEFT
    if(cc.x > 0 && cc.y > 0 && (currval > 2 || currval == 1)) {
        XY target(cc.x-1, cc.y-1);
        int tarVal = board[target.x][target.y];
        if((target.x > 0 && target.y > 0)) {
            if ((tarVal == REGULAR || tarVal == KINGVAL) && board[target.x-1][target.y-1] == 0) {
                hasAJump = true;
                //ADD JUMP TO LIST
                gb->setBoard(board);
                XY jumpTo(target.x-1, target.y-1);
                gb->doMove(cc, jumpTo);

                isLastMove = (gb->getMoves(jumpTo, gb->board,myvectofgb, list, pathlength+1, requestMove, moveListIdx, player1)); //, mylistOfMoves, moveNum, ++movePathNum));
            }
        }
    }
    //TOP RIGHT
    if(cc.x > 0 && cc.y < 7 && (currval > 2 || currval == 1)) {
        XY target(cc.x-1, cc.y+1);
        int tarVal = board[target.x][target.y];
        if ((tarVal == REGULAR || tarVal == KINGVAL) && board[target.x-1][target.y+1] == 0 && (target.x > 0 && target.y < 7)) {
            hasAJump = true;
            //ADD JUMP TO LIST
            gb->setBoard(board);
            XY jumpTo(target.x-1, target.y+1);
            gb->doMove(cc, jumpTo);


            isLastMove = (gb->getMoves(jumpTo, gb->board,myvectofgb, list, pathlength+1, requestMove, moveListIdx, player1)); //, mylistOfMoves, moveNum, ++movePathNum));
        }
    }
    //BOTTOM LEFT
    if((cc.x < 7 && cc.y > 0) && currval >= 2) {
        XY target(cc.x+1, cc.y-1);
        int tarVal = board[target.x][target.y];
        if ((tarVal == REGULAR || tarVal == KINGVAL) && board[target.x+1][target.y-1] == 0 && (target.x < 7 && target.y > 0)) {
            hasAJump = true;
            //ADD JUMP TO LIST
            gb->setBoard(board);
            XY jumpTo(target.x+1, target.y-1);
            gb->doMove(cc, jumpTo);

            isLastMove = (gb->getMoves(jumpTo, gb->board,myvectofgb, list, pathlength+1, requestMove, moveListIdx, player1)); //, mylistOfMoves, moveNum, ++movePathNum));
        }
    }
    //BOTTOM RIGHT
    if((cc.x < 7 && cc.y < 7) && currval >= 2) {
        XY target(cc.x+1, cc.y+1);
        int tarVal = board[target.x][target.y];
        if ((tarVal == REGULAR || tarVal == KINGVAL) && board[target.x+1][target.y+1] == 0 && (target.x < 7 && target.y < 7)) {
            hasAJump = true;
            //ADD JUMP TO LIST
            gb->setBoard(board);
            XY jumpTo(target.x+1, target.y+1);
            gb->doMove(cc, jumpTo);

            isLastMove = (gb->getMoves(jumpTo, gb->board,myvectofgb, list, pathlength+1, requestMove, moveListIdx, player1)); //, mylistOfMoves, moveNum, ++movePathNum));
        }
    }  

    if(isLastMove && pathlength != 0) {
        if(requestMove) {
            printXYMovesList(list, pathlength, moveListIdx);
            (*moveListIdx)++;
        }
        for(int j = 0; j < 8; j++) {
            if(board[0][j] == 1) {
                board[0][j] = 3;
            }
            if(board[7][j] == 2) {
                board[7][j] = 4;
            }
        }
        setBoard(board);
        myvectofgb.push_back(gb);
        return false;
    }
    else {
        delete gb;
    }
    return false;
}

void GameBoard::getRegularMoves(XY cc, unsigned char board[][8], std::vector<GameBoard*> &myvectofgb, bool requestMove, int *moveListIdx) {
	if(hasAJump) {
		return;
    }
    int currval = board[cc.x][cc.y];
    //Check Top Left
    if (cc.x > 0 && cc.y > 0 && (currval > 2 || currval == 1)) {
        XY target(cc.x-1, cc.y-1);
        if (board[target.x][target.y] == 0) {
            //ADD MOVE
        	GameBoard *gb = new GameBoard();
			gb->setBoard(board);
            gb->doMove(cc, target);  
            myvectofgb.push_back(gb);
            if(requestMove) {
                std::cout << "  Move " << *moveListIdx << ": " << cc.toString() << " -> " << target.toString() << std::endl;
                (*moveListIdx)++;
            }
        }
    }
    //Check Top Right
    if (cc.x > 0 && cc.y < 7 && (currval > 2 || currval == 1)){
        XY target(cc.x-1, cc.y+1);
        if (board[target.x][target.y] == 0) {
            //ADD MOVE
        	GameBoard *gb = new GameBoard();
			gb->setBoard(board);
            gb->doMove(cc, target);  
            myvectofgb.push_back(gb);
            if(requestMove) {
                std::cout << "  Move " << *moveListIdx << ": " << cc.toString() << " -> " << target.toString() << std::endl;
                (*moveListIdx)++;
            }
        }
    }
    //Check Bottom Left
    if (cc.x < 7 && cc.y > 0 && currval >= 2) {
        XY target(cc.x+1, cc.y-1);
        if (board[target.x][target.y] == 0) {
            //ADD MOVE
        	GameBoard *gb = new GameBoard();
			gb->setBoard(board);
            gb->doMove(cc, target);  
            myvectofgb.push_back(gb);
            if(requestMove) {
                std::cout << "  Move " << *moveListIdx << ": " << cc.toString() << " -> " << target.toString() << std::endl;
                (*moveListIdx)++;
            }

        }
    }
    //Check Bottom Right
    if (cc.x < 7 && cc.y < 7 && currval >= 2) {
        XY target(cc.x+1, cc.y+1);
        if (board[target.x][target.y] == 0) {
            //ADD MOVE
        	GameBoard *gb = new GameBoard();
            gb->setBoard(board);
            gb->doMove(cc, target);  
            myvectofgb.push_back(gb);
            if(requestMove) {
                std::cout << "  Move " << *moveListIdx << ": " << cc.toString() << " -> " << target.toString() << std::endl;
                (*moveListIdx)++;
            }
        }
    }
}




void GameBoard::getAllP1Moves(bool requestMove, int *moveListIdx) {
    player1 = true;
    for(int i = 0; i < number_P1_pieces; i++) {
        //std::cout << "FOR PIECE: " << i;
        XY cc = P1_pieces[i];
        getMoves(cc, board, vectOfGb, XYMovesList, 0, requestMove, moveListIdx, player1); //, listOfMoves, numOfMoves, pathNum); //xinmin: top "Steps" is NULL
    }
    for(int j = 0; j < 8; j++) {
        if(board[0][j] == 1) {
            board[0][j] = 3;
        }
        if(board[7][j] == 2) {
            board[7][j] = 4;
        }
    }
    setBoard(board);
    if(hasAJump) return;
    else{
        for(int i = 0; i < vectOfGb.size(); i++) {
            delete vectOfGb[i];
        }
        vectOfGb.clear();
    }
    for(int i = 0; i < number_P1_pieces; i++) {
        if(!hasAJump) {
            XY cc = P1_pieces[i];
		    getRegularMoves(cc, board, vectOfGb, requestMove, moveListIdx);
        }
    }
    for(int j = 0; j < 8; j++) {
        if(board[0][j] == 1) {
            board[0][j] = 3;
        }
        if(board[7][j] == 2) {
            board[7][j] = 4;
        }
    }
    setBoard(board);
}

void GameBoard::getAllP2Moves(bool requestMove, int *moveListIdx) {
    player1 = false;
    for(int i = 0; i < number_P2_pieces; i++) {
        XY cc = P2_pieces[i];
        getMoves(cc, board, vectOfGb, XYMovesList, 0, requestMove, moveListIdx, player1); //, listOfMoves, numOfMoves, pathNum); //xinmin: top "Steps" is NULL
    }

    setBoard(board);
    if(hasAJump) return;
    else{
        for(int i = 0; i < vectOfGb.size(); i++) {
           delete vectOfGb[i];
        }
        vectOfGb.clear();
    }
    for(int i = 0; i < number_P2_pieces; i++) {
        XY cc = P2_pieces[i];
        if(!hasAJump) {
            getRegularMoves(cc, board, vectOfGb, requestMove, moveListIdx);
        }
    }
    for(int j = 0; j < 8; j++) {
        if(board[0][j] == 1) {
            board[0][j] = 3;
        }
        if(board[7][j] == 2) {
            board[7][j] = 4;
        }
    }
    setBoard(board);

}

void GameBoard::printAllP1Moves() {
    std::cout << "vectofGb size: " << vectOfGb.size() << std::endl;
    for(int i = 0; i < vectOfGb.size(); i++) {
        std::cout << "====================" << std::endl;
        vectOfGb[i]->printBoard();
    }
}

void GameBoard::printP1MoveList() {
	std::cout << "listOfMoves size: " << listOfMoves.size() << std::endl;
	for (int i = 0; i < listOfMoves.size(); i++) {
		std::cout << "====================" << std::endl;
		listOfMoves[i]->print();
	}
}

void GameBoard::printXYMovesList(XY list[], int plength, int *moveListIdx) {
    std::cout << "  Move " << *moveListIdx << ": ";
    for(int i = 0; i <= plength; i++) {
        std::cout << list[i].toString();
        if(i != plength)
            std::cout << " -> ";
    }
    std::cout << std::endl;
}

int GameBoard::isWin(int whoseturn) {
    if(whoseturn == 1)
        getAllP1Moves(false, NULL);
    else
        getAllP2Moves(false, NULL);
    if(vectOfGb.size() == 0){
        return 1;
    }
    if(number_P2_pieces == 0){
        return 2;
    }
    if(number_P1_pieces == 0){
        return 3;
    }
return 0;
}


bool GameBoard::SameAsReg(GameBoard *parent) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(!(parent->board[i][j] == board[i][j]))
                return true;
        }
    }
    return false;
}


void GameBoard::getMovesGeneral(int userplayernum, int *idx) {
    if(userplayernum == 1)
        getAllP1Moves(true, idx);
    else
        getAllP2Moves(true, idx);
}

void GameBoard::getMovesGeneralDontDisplayMoves(int userplayernum, int *idx) {
    if(userplayernum == 1)
        getAllP1Moves(false, idx);
    else
        getAllP2Moves(false, idx);
}



void GameBoard::printInformation() {
    std::cout << "hasAJump: " << hasAJump << " P1n: " << number_P1_pieces << " P2n: " << number_P2_pieces << std::endl;
}









