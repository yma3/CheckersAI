//
// Created by New on 11/4/2017.
//

#ifndef CHECKERSAI_COMPOSITE_H
#define CHECKERSAI_COMPOSITE_H

#include <iostream>
#include <vector>
#include "GameBoard.h"

class Component {
public:
    virtual void traverse() = 0;
    virtual void traverseSet(std::vector < Component * > &leafList) = 0;
    virtual void clean() = 0;
    virtual bool isRepeat(Component* c) = 0;
};

class Leaf: public Component {
public:
    XY start;
    XY end;
public:
    Leaf(XY startcc, XY endcc) {
        start = startcc;
        end = endcc;
    }

    void traverse();
    void traverseSet(std::vector < Component * > &leafList);
    void clean() {}

    bool isReverse(Leaf *c) {

        return c->start.equal(end) && c->end.equal(start);
    }

    bool isSame(Leaf *c) {
        return c->start.equal(start) && c->end.equal(end);
    }
    bool isRepeat(Component *c) {
        Leaf *lp = dynamic_cast<Leaf*>(c);
        if(lp == NULL)
            return false;
        return isReverse(lp) || isSame(lp);
    }
};
class Composite: public Component {
public:
    std::vector < Component * > children;
    bool isJump;
    XY origin;
public:
    //Composite() {}
    Composite(bool isJmp):isJump(isJmp){}
    Composite(bool isJmp, XY orig):isJump(isJmp),origin(orig){}
    bool add(Component *ele);
    void traverse();
    void traverseSet(std::vector < Component * > &leafList);
    void traverseFindMove();
    void clean();
    bool isRepeat(Component *c) {return false;}
    bool isNotLoop(XY xy) {
        if(children.size() == 0)
            return false;
        Leaf *lp = dynamic_cast<Leaf*>(children[0]);
        if(lp == NULL)
            return false;
        return lp->start.equal(xy);

    }

};
#endif //CHECKERSAI_COMPOSITE_H
