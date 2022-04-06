#include <iostream>
#include "Graph.h"
#include "GraphWorker.h"

void runFromSeeds(bool mt = false, size_t thCount = 4) {
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

        size_t answer;
        time_t t = time(nullptr);
        if (mt) {
            answer = gw->mtFindMaxNodesArray(thCount);
        } else {
            answer = gw->findMaxNodesArray();
        }
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
        std::cout << "Answer: " << gw->findMaxNodesArray();
    }
    else {
        std::cout << "Can`t run control test.";
    }

    std::cout << std::endl << std::endl;

    // Запуск тестов
    std::cout << "mt4:" << std::endl;
    runFromSeeds(true, 4);

    std::cout << "mt64:" << std::endl;
    runFromSeeds(true, 64);

    std::cout << std::endl <<  "mt1:" << std::endl;
    runFromSeeds(true, 1);

    return 0;
}
