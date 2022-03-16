#include <iostream>
#include "Graph.h"
#include "GraphWorker.h"

void runFromSeeds() {
    std::ifstream fsi;
    std::ofstream fso;
    fsi.open("../tests/seeds.txt", std::_S_in);
    fso.open("../tests/seeds-answers.txt", std::_S_out);

    while (!fsi.eof()) {
        size_t size;
        int seed;
        fsi >> size >> seed;

        auto* gw = new GraphWorker(new Graph(size));
        gw->fillRandom(seed);
        std::cout << size << ' ' << seed << ' ';

        time_t t = time(nullptr);
        size_t answer = gw->findMaxNodesArray();
        time_t t2 = time(nullptr);

        delete gw->getGraph();
        delete gw;

        fso << size << ' ' << seed << ' ' << " (ans: " << answer << ", time: " << difftime(t2, t) << ')' << std::endl;
        std::cout << " (ans: " << answer << ", time: " << difftime(t2, t) << ')' << std::endl;
    }
    fsi.close();
    fso.close();
}

int main() {
    // Контрольный запуск
    Graph* g = Graph::readFromFile("../tests/1.txt");
    if (g != nullptr) {
        auto* gw = new GraphWorker(g);
        gw->print()->getGraph()->saveToFile("../tests/saved.txt", true);
        std::cout << "Answer: " << gw->findMaxNodesArray() << std::endl << std::endl;
    }
    else {
        std::cout << "Can`t run control test."
    }

    // Запуск тестов
    runFromSeeds();

    return 0;
}
