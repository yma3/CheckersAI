//
// Created by New on 11/4/2017.
//
#include <iostream>
#include <algorithm>
#include "GameBoard.h"

void GameBoard::setBoard(unsigned char myboard[][8]) {
    for(int i=0; i<8; ++i) {
        for(int j=0; j<8; ++j) {
            board[i][j] = myboard[i][j];
        }
    }
    setPieces();
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

/*void GameBoard::printBoard() {
    std::cout << "=========================================" << std::endl;
    std::cout << "    0 1 2 3 4 5 6 7 " << std::endl;
    std::cout << "-------------------" << std::endl;

    for(int i=0; i<8; ++i) {
        std::cout << i << " | ";
        for (int j = 0; j < 8; ++j) {
            if(board[i][j] != 0)
                std::cout << (int)board[i][j] << " ";
            else
                std::cout << "0 ";
        }
        std::cout << std::endl;
    }
}*/


void GameBoard::printBoard() {
    std::cout << std::endl << "=================================";
    for (int i = 0; i <8; i++) {
        std::cout << std::endl << "+---+---+---+---+---+---+---+---+"<< std::endl;
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
                    std::cout << "\033[0;96;40m " << "8" << " " << "\033[0m";   
            }
            else {
                std::cout << "  " << " " << "\033[0m";
            }
            if(j == 7) {
                std::cout << "|";
            }
        }
        if(i == 7) {
            std::cout << std::endl << "+---+---+---+---+---+---+---+---+"<< std::endl;
        }
    }
    printInfo();
}

void GameBoard::printInfo() {
    std::cout << "================================="<< std::endl;
    std::cout << "Player 1: " << "\033[0;96;40m   " << "o" << " " << "\033[0m" << "     ";
    std::cout << "Player 2: " << "\033[0;91;40m " << "o" << " " << "\033[0m" << std::endl;
    std::cout << "Player 1 K: " << "\033[0;96;40m " << "8" << " " << "\033[0m" << "   ";
    std::cout << "Player 2 K: " << "\033[0;91;40m " << "8" << " " << "\033[0m" <<std::endl;
    std::cout << "================================="<< std::endl;
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

void GameBoard::setHeuristic() {
    int player2score = 0;
    int player1score = 0;
    int edgeweight = 0;

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(i == 0 || i == 7 || j == 0 || j == 7) {
                edgeweight = 2;
            }
            else {
                edgeweight = 0;
            }
            unsigned char pieceVal = board[i][j];
            switch(pieceVal) {
                case 0: break;
                case 1: player2score += 5+edgeweight; break;
                case 2: player1score += 5+edgeweight; break;
                case 3: player2score += 10+edgeweight; break;
                case 4: player1score += 10+edgeweight; break;
            }
            if(i < 4 && (pieceVal == 1)) {
                player1score += 2;
            }
            if(i > 4 && pieceVal == 2) {
                player2score +=2;
            }
    
            //std::cout << "MAXSCORE: " << player2score << "MINSCORE: " << player1score << std::endl;
        }



    }
    heuristicValue = player1score - player2score;
    //std::cout << "\033[7;47m" << "SCORE: " << heuristicValue<< std::endl;
    //std::cout << "\033[7;0m";
    return;
}

void GameBoard::doMove(XY start, XY end) {
    //std::cout<<"DOING MOVE" << start.toString() << " , " << end.toString() << std::endl;
    int dx = end.x - start.x;
    if(dx == 2 || dx == -2) {
        board[(start.x+end.x)/2][(start.y+end.y)/2] = 0;
    }
    board[end.x][end.y] = board[start.x][start.y];
    board[start.x][start.y] = 0;
}




bool GameBoard::getMoves(Steps *theSteps, XY cc, unsigned char board[][8], std::vector<GameBoard*> &myvectofgb) { //std::vector<std::vector<Moves>> &mylistOfMoves, int &moveNum, int &movePathNum) {
    /*XY orig;
    if(movePathNum == 0) {
        std::vector<Moves> newCol;
        mylistOfMoves.push_back(newCol);
        movePathNum;
        orig = cc;
    }*/


    //std::cout << "STARTING FROM " << (int)cc.x << " , " << (int)cc.y << std::endl;
    bool isLastMove = true;
    int currval = board[cc.x][cc.y];
    GameBoard *gb = new GameBoard();
    gb->setBoard(board);
    if(player1) {REGULAR = 2; KINGVAL = 4;}
    else {REGULAR = 1; KINGVAL = 3;}
    //TOP LEFT
    if(cc.x > 0 && cc.y > 0) {
        XY target(cc.x-1, cc.y-1);
        int tarVal = board[target.x][target.y];
        if ((tarVal == REGULAR || tarVal == KINGVAL) && board[target.x-1][target.y-1] == 0 && (target.x > 0 && target.y > 0)) {
            //std::cout << "TOP LEFT!" << std::endl;
            hasAJump = true;
            //ADD JUMP TO LIST
            gb->setBoard(board);
            XY jumpTo(target.x-1, target.y-1);
            gb->doMove(cc, jumpTo);
            //mylistOfMoves[moveNum].push_back(orig, cc, jumpTo);
            //gb->printBoard();
			Steps *pSteps = theSteps;
			if (pSteps == NULL) {
				pSteps = new Steps();
				currentPieceSteps->add(pSteps);
			}
			pSteps->add(cc, jumpTo);
            isLastMove = (gb->getMoves(pSteps, jumpTo, gb->board,myvectofgb)); //, mylistOfMoves, moveNum, ++movePathNum));
            //std::cout << isLastMove << " :isLastMove" << std::endl;
        }
    }
    //TOP RIGHT
    if(cc.x > 0 && cc.y < 7) {
        XY target(cc.x-1, cc.y+1);
        int tarVal = board[target.x][target.y];
        if ((tarVal == REGULAR || tarVal == KINGVAL) && board[target.x-1][target.y+1] == 0 && (target.x > 0 && target.y < 7)) {
            //std::cout << "TOP RIGHT!" << std::endl;
            hasAJump = true;
            //ADD JUMP TO LIST
            gb->setBoard(board);
            XY jumpTo(target.x-1, target.y+1);
            gb->doMove(cc, jumpTo);
            //mylistOfMoves[moveNum].push_back(orig, cc, jumpTo);
            //gb->printBoard();
			Steps *pSteps = theSteps;
			if (pSteps == NULL) {
				pSteps = new Steps();
				currentPieceSteps->add(pSteps);
			}
			pSteps->add(cc, jumpTo);
            isLastMove = (gb->getMoves(pSteps, jumpTo, gb->board,myvectofgb)); //, mylistOfMoves, moveNum, ++movePathNum));
        }
    }
    //BOTTOM LEFT
    if((cc.x < 7 && cc.y > 0) || currval > 2) {
        XY target(cc.x+1, cc.y-1);
        int tarVal = board[target.x][target.y];
        if ((tarVal == REGULAR || tarVal == KINGVAL) && board[target.x+1][target.y-1] == 0 && (target.x < 7 && target.y > 0)) {
            //std::cout << "BOTTOM LEFT!" << std::endl;
            hasAJump = true;
            //ADD JUMP TO LIST
            gb->setBoard(board);
            XY jumpTo(target.x+1, target.y-1);
            gb->doMove(cc, jumpTo);
            //mylistOfMoves[moveNum].push_back(orig, cc, jumpTo);
            //gb->printBoard();

			Steps *pSteps = theSteps;
			if (pSteps == NULL) {
				pSteps = new Steps();
				currentPieceSteps->add(pSteps);
			}
			pSteps->add(cc, jumpTo);

            isLastMove = (gb->getMoves(pSteps, jumpTo, gb->board,myvectofgb)); //, mylistOfMoves, moveNum, ++movePathNum));
        }
    }
    //BOTTOM RIGHT
    if((cc.x < 7 && cc.y < 7) || currval > 2) {
        
        XY target(cc.x+1, cc.y+1);
        int tarVal = board[target.x][target.y];
        if ((tarVal == REGULAR || tarVal == KINGVAL) && board[target.x+1][target.y+1] == 0 && (target.x < 7 && target.y < 7)) {
            //std::cout << "BOTTOM RIGHT! " << std::endl;
            hasAJump = true;
            //ADD JUMP TO LIST
            gb->setBoard(board);
            XY jumpTo(target.x+1, target.y+1);
            gb->doMove(cc, jumpTo);
            //mylistOfMoves[moveNum].push_back(orig, cc, jumpTo);
            //gb->printBoard();
			Steps *pSteps = theSteps;
			if (pSteps == NULL) {
				pSteps = new Steps();
				currentPieceSteps->add(pSteps);
			}
			pSteps->add(cc, jumpTo);

            isLastMove = (gb->getMoves(pSteps, jumpTo, gb->board,myvectofgb)); //, mylistOfMoves, moveNum, ++movePathNum));
        }
    }  

    //std::cout << "NO MORE MOVES HERE" << std::endl;

    //std::cout << "isLastMove: " << isLastMove << std::endl;
    //std::cout << "++++++++++++" << std::endl;
    if(isLastMove) {
        //push onto vector
        //gb->printBoard();
        //std::cout << "PUSHING BACK INTO VECTOR" << std::endl;
        myvectofgb.push_back(gb);
        std::cout << "PUSHED BACK!!!" << std::endl;
        gb->printBoard();
        std::cout << "^^ PUSHED BACK ^^" << std::endl;
        //moveNum++;
        //movePathNum = 0;
        //mylistOfMoves.push_back(mylistOfMoves[moveNum]);
        //std::cout << "Push successful. Size of vector is: " << vectOfGb.size() << std::endl;
        return false;
    }
    //std::cout << "RETURNING TRUE" << std::endl;
    return false;
}

void GameBoard::getRegularMoves(XY cc, unsigned char board[][8], std::vector<GameBoard*> &myvectofgb) {
	if(hasAJump) {
		//std::cout << "JUMPS FOUND." << std::endl;
		return;
	} //else {std::cout<<"NO JUMPS FOUND" << std::endl;}
    int currval = board[cc.x][cc.y];
    //Check Top Left
    if (cc.x > 0 && cc.y > 0 && (currval > 2 || currval == 1)) {
        XY target(cc.x-1, cc.y-1);
        if (board[target.x][target.y] == 0) {
            //ADD MOVE
        	GameBoard *gb = new GameBoard();
			gb->setBoard(board);
            gb->doMove(cc, target);  
            //gb->printBoard();          	
            myvectofgb.push_back(gb);
            //std::cout<<"SIZE OF VECTOFGB: " << myvectofgb.size() << std::endl;
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
            //gb->printBoard();            	
            myvectofgb.push_back(gb);
            //std::cout<<"SIZE OF VECTOFGB: " <<myvectofgb.size() << std::endl;

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
            //gb->printBoard();   
            myvectofgb.push_back(gb);
            //std::cout<<"SIZE OF VECTOFGB: " <<myvectofgb.size() << std::endl;

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
            //gb->printBoard();   
            myvectofgb.push_back(gb);
            //std::cout<<"SIZE OF VECTOFGB: " <<myvectofgb.size() << std::endl;

        }
    }
}




void GameBoard::getAllP1Moves() {
    player1 = true;
    for(int i = 0; i < number_P1_pieces; i++) {
        //std::cout << "FOR PIECE: " << i << std::endl;
        XY cc = P1_pieces[i];
        //std::cout << cc.toString() << std::endl;
		currentPieceSteps = new PieceSteps(); // for every piece, this is different
        getMoves(NULL, cc, board, vectOfGb); //, listOfMoves, numOfMoves, pathNum); //xinmin: top "Steps" is NULL
		listOfMoves.push_back(currentPieceSteps);
        if(!hasAJump) {
            //std::cout << "Size: " << vectOfGb.size() << std::endl;
            vectOfGb.pop_back();
            std::cout << "cleared!, " << vectOfGb.size() << std::endl;
			getRegularMoves(cc, board, vectOfGb);
        }
    }
}

void GameBoard::getAllP2Moves() {
    player1 = false;
    for(int i = 0; i < number_P2_pieces; i++) {
        std::cout << "FOR PIECE IN PLAYER 2: " << i << std::endl;
        XY cc = P2_pieces[i];
        //std::cout << cc.toString() << std::endl;
        currentPieceSteps = new PieceSteps(); // for every piece, this is different
        getMoves(NULL, cc, board, vectOfGb); //, listOfMoves, numOfMoves, pathNum); //xinmin: top "Steps" is NULL
        listOfMoves.push_back(currentPieceSteps);
        std::cout << i << " hasJump?: " << hasAJump << std::endl;
    //MOVE TO IF FOR MORE EFFICIENCY
    //std::cout << "vect size: " << vectOfGb.size() << std::endl;
        if(!hasAJump) {
            vectOfGb.pop_back();
            std::cout << "cleared!, " << vectOfGb.size() << std::endl;
            getRegularMoves(cc, board, vectOfGb);
        }
    }
}

void GameBoard::printAllP1Moves() {
    std::cout << "vectofGb size: " << vectOfGb.size() << std::endl;
    for(int i = 0; i < vectOfGb.size(); i++) {
        std::cout << "====================" << std::endl;
        vectOfGb[i]->printBoard();
    }
}

/*void GameBoard::printP1MoveList() {
    for (std::vector<std::vector<XY>>::size_type i = 0; i < listOfMoves.size(); i++) {
        for (std::vector<XY>::size_type j = 0; j < listOfMoves[i].size(); j++) {
            std::cout << "MOVE TO: " << listOfMoves[i][j].end.toString() << std::endl;
        }
    }
}*/

void GameBoard::printP1MoveList() {
	std::cout << "listOfMoves size: " << listOfMoves.size() << std::endl;
	for (int i = 0; i < listOfMoves.size(); i++) {
		std::cout << "====================" << std::endl;
		listOfMoves[i]->print();
	}
}

bool GameBoard::isWin() {
    if(vectOfGb.size() == 0)
        return true;
    if(number_P2_pieces == 0)
        return true;
    if(number_P1_pieces == 0)
        return true;
return false;
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
















