//
// Created by New on 11/4/2017.
//

#ifndef CHECKERSAI_CHECKERCOMPOSITE_H
#define CHECKERSAI_CHECKERCOMPOSITE_H

#include <iostream>
#include <vector>
#include "GameBoard.h"

class CheckerComponent {
public:
    virtual void traverse() = 0;
};

class CheckerLeaf: public CheckerComponent {
public:
    GameBoard *gb;

    void traverse();

};
class CheckerComposite: public CheckerComponent {
public:
    std::vector < CheckerComponent * > children;
public:
    //CheckerComposite() {}
    void add(CheckerComponent *ele);
    void traverse();

};
#endif //CHECKERSAI_CHECKERCOMPOSITE_H
