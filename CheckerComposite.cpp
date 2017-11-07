//
// Created by New on 11/4/2017.
//

#include "CheckerComposite.h"

void CheckerLeaf::traverse() {
    //std::cout << value;
}

void CheckerComposite::add(CheckerComponent *ele) {
    children.push_back(ele);
}
void CheckerComposite::traverse() {
    for (int i = 0; i < children.size(); i++) {
        children[i]->traverse();
    }
}
