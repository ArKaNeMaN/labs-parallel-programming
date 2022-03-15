//
// Created by arkan on 16.02.2022.
//

#include "GraphWorker.h"

GraphWorker::GraphWorker(Graph* g) {
    this->g = g;
}

void GraphWorker::print() {
    std::cout << "Nodes:" << std::endl;
    for (size_t i = 0; i < g->getSize(); i++) {
        std::cout << g->getNode(i) << "\t";
    }
    std::cout << std::endl << std::endl;

    std::cout << "Links:" << std::endl;
    for (size_t i = 0; i < g->getSize(); i++) {
        for (size_t j = 0; j < g->getSize(); j++) {
            std::cout << g->getLink(i, j) << "\t";
        }

        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void GraphWorker::fillRandom() {
    // gen nodes weight
    for (size_t i = 0; i < g->getSize(); i++) {

    }

    // gen links
//    size_t
//    for (size_t i = 0; i < g->getSize(); i++) {
//        for (size_t j = 0; j < g->getSize(); j++) {
//            if () {
//
//            }
//        }
//    }
}


