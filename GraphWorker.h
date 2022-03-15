//
// Created by arkan on 16.02.2022.
//

#ifndef CPP_FINDMAXGRAPHPART_GRAPHWORKER_H
#define CPP_FINDMAXGRAPHPART_GRAPHWORKER_H

#include "Graph.h"
#include <iostream>

class GraphWorker {
private:
    Graph* g;

public:
    explicit GraphWorker(Graph*);

    void print();
    void fillRandom();
};

#endif //CPP_FINDMAXGRAPHPART_GRAPHWORKER_H
