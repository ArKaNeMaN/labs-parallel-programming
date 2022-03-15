#include <iostream>
#include "Graph.h"
#include "GraphWorker.h"

int main() {
    Graph* g = Graph::readFromFile("../tests/1.txt");
    if (g == nullptr) {
        exit(1);
    }

    auto* gw = new GraphWorker(g);
    gw->print()->getGraph()->saveToFile("../tests/saved.txt", true);
    std::cout << "Answer: " << gw->findMaxNodesArray() << std::endl;

    std::cout << "\n\n";

    auto* gw2 = new GraphWorker(new Graph(5));
    gw2->fillRandom(50)->print()->getGraph()->saveToFile("../tests/latest-random.txt", true);
    std::cout << "Answer: " << gw2->findMaxNodesArray() << std::endl;

    return 0;
}
