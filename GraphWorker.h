//
// Created by arkan on 16.02.2022.
//

#ifndef CPP_FINDMAXGRAPHPART_GRAPHWORKER_H
#define CPP_FINDMAXGRAPHPART_GRAPHWORKER_H

#include "SharedQueue.h"
#include "Graph.h"
#include <thread>
#include <iostream>
#include <limits>
#include <queue>

class GraphWorker {
private:
    Graph* g;

    size_t findMaxNodesArrayFromNode(size_t node);

public:
    explicit GraphWorker(Graph*);

    GraphWorker *print();
    GraphWorker *fillRandom(int seed = 0);
    Graph *getGraph();
    size_t findMaxNodesArray();
    size_t mtFindMaxNodesArray(size_t threadsCount = 8);
};

#endif //CPP_FINDMAXGRAPHPART_GRAPHWORKER_H
