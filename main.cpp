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

    auto* gw2 = new GraphWorker(new Graph(250));
    gw2->fillRandom(222)->getGraph()->saveToFile("../tests/latest-random.txt", true);

    // TODO: Брать время в миллисекундах
    // ---------------------------
    time_t t = time(nullptr);
    size_t answer = gw2->findMaxNodesArray();
    time_t t2 = time(nullptr);
    // ---------------------------

    std::cout << "Answer: " << answer << std::endl;
    std::cout << "diff time: " << difftime(t2, t) << std::endl;

    return 0;
}
