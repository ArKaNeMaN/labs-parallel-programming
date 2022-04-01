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
#include <chrono>

class GraphWorker {
private:
    Graph* g;

public:
    explicit GraphWorker(Graph*);

    GraphWorker *print();
    GraphWorker *fillRandom(int seed = 0);
    Graph *getGraph();
    size_t findMaxNodesArray();
    size_t mtFindMaxNodesArray(size_t threadsCount = 8);

    size_t findMaxNodesArrayFromNode(size_t node);
};

template <typename I, typename O>
struct GraphWorker_ThreadParams {
    GraphWorker* gw;
    SharedQueue<I>* itemsQueue;
    SharedQueue<O>* answersQueue;
};

#endif //CPP_FINDMAXGRAPHPART_GRAPHWORKER_H
