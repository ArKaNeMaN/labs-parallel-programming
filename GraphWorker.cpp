//
// Created by arkan on 16.02.2022.
//

#include "GraphWorker.h"

GraphWorker::GraphWorker(Graph *g) {
    this->g = g;
}

GraphWorker *GraphWorker::print() {
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

    return this;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"

GraphWorker *GraphWorker::fillRandom(int seed) {
    std::srand(seed);

    // gen nodes weight
    for (size_t i = 0; i < g->getSize(); i++) {
        g->setNode(i, std::rand() % 100 + 1);
    }

    // reset matrix
    for (size_t x = 0; x < g->getSize(); x++) {
        for (size_t y = 0; y < g->getSize(); y++) {
            g->setLink(x, y, 0);
        }
    }

    // gen links
    size_t linksNum = std::rand() % (g->getSize() * g->getSize() / 2) + 1;
    for (size_t i = 0; i < linksNum; i++) {
        size_t x, y, c = 0;
        do {
            x = std::rand() % g->getSize();
            y = std::rand() % g->getSize();
            c++;
        } while ((g->getLink(x, y) || x == y) && c < g->getSize());

        if (g->getLink(x, y)) {
            continue;
        }

        g->setLink(x, y, std::rand() % 100 + 1);
    }

    return this;
}

#pragma clang diagnostic pop

Graph *GraphWorker::getGraph() {
    return g;
}

size_t GraphWorker::findMaxNodesArrayFromNode(size_t node) {
    std::vector<bool> marked, used;
    marked.resize(g->getSize());
    used.resize(g->getSize());

    for (size_t i = 0; i < g->getSize(); i++) {
        marked[i] = false;
        used[i] = false;
    }

    weight_t answer = 0;

    std::queue<size_t> q;
    q.push(node);

    // Обход в ширину от начальной вершины
    while (!q.empty()) {
        size_t x = q.front();
        q.pop();

        // Если не рядом и не использована, то помечать и прбавлять её вес
        if (!used[x] && !marked[x]) {
            used[x] = true;
            marked[x] = true;
            answer += g->getNode(x);
        }

        // Для каждой соседней вершины
        for (size_t y = 0; y < g->getSize(); y++) {
            if (!marked[y] && (g->getLink(x, y) || g->getLink(y, x))) {
                // Если не помечена, то пушить в очередь и помечать, если текущая вершина использована
                marked[y] = used[x];
                q.push(y);
            }
        }
    }

    marked.clear();
    used.clear();

    return answer;
}

size_t GraphWorker::mtFindMaxNodesArray(size_t threadsCount) {
    using namespace std::chrono_literals;

    SharedQueue<size_t> q, answers;

    for (size_t i = 0; i < g->getSize(); i++) {
        q.push(i);
    }

    GraphWorker_ThreadParams<size_t, size_t> params{};
    params.gw = this;
    params.itemsQueue = &q;
    params.answersQueue = &answers;

    std::vector<std::thread> threads;
    for (size_t i = 0; i < threadsCount; i++) {
        std::thread th = std::thread([&](GraphWorker_ThreadParams<size_t, size_t> params) {
            size_t node;
            while (params.itemsQueue->try_pop(node, 100ms)) {
                size_t ans = params.gw->findMaxNodesArrayFromNode(node);
                params.answersQueue->push(ans);
            }
        }, params);
        threads.push_back(std::move(th));
    }

    for (auto &thread: threads) {
        thread.join();
    }

    size_t answer = 0;
    while (answers.size() > 0) {
        answer = std::max(answers.pop(), answer);
    }

    return answer;
}

size_t GraphWorker::findMaxNodesArray() {
    size_t answer = 0;
    for (size_t i = 0; i < g->getSize(); i++) {
        answer = std::max(answer, findMaxNodesArrayFromNode(i));
    }

    return answer;
}


