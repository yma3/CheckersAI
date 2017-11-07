//
// Created by New on 11/4/2017.
//

#include "Composite.h"

void Leaf::traverse() {
    std::cout << start.toString() << " -> " << end.toString();
}
void Leaf::traverseSet(std::vector < Component * > &leafList) {
    //std::cout << "PUSHING BACK MOVE" << std::endl;
    leafList.push_back(this);
}

bool Composite::add(Component *ele) {
    for (int i = 0; i < children.size(); i++) {
        if(children[i]->isRepeat(ele))
            return false;
    }
    //std::cout << "ADDING AN ELEMENT: " << ele << std::endl;
    children.push_back(ele);
    return true;
}
void Composite::traverse() {
    std::cout<<" -- composite size: "<< children.size() << std::endl;
    for (int i = 0; i < children.size(); i++) {
        // 5. Use polymorphism to delegate to children
        //if (!isJump)
        std::cout<<std::endl <<" -- composite: "<< i ;
        children[i]->traverse();
    }
}

void Composite::clean() {
    for (int i = 0; i < children.size(); i++) {
        Component *c = children[i];
        Leaf *lp = dynamic_cast<Leaf*>(c);
        if(lp == NULL) 
            delete lp;
        else 
            c->clean();
    }
}

void Composite::traverseSet(std::vector < Component * > &leafList) {
    for (int i = 0; i < children.size(); i++) {
        children[i]->traverseSet(leafList);
    }
}
