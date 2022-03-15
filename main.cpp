#include <iostream>
#include "Graph.h"
#include "GraphWorker.h"

int main() {
    Graph* g = Graph::readFromFile("./tests/1.txt");
    if (g == nullptr) {
        exit(1);
    }

    auto* gw = new GraphWorker(g);
    gw->print();

    return 0;
}
