//
// Created by New on 11/4/2017.
//
#include <iostream>
#include "GameBoard.h"

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
                case 1: player2score += 3+edgeweight; break;
                case 2: player1score += 3+edgeweight; break;
                case 3: player2score += 5+edgeweight; break;
                case 4: player1score += 5+edgeweight; break;
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