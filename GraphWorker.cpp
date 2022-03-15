//
// Created by arkan on 16.02.2022.
//

#include "GraphWorker.h"

GraphWorker::GraphWorker(Graph* g) {
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

//    std::cout << std::endl << "node: " << node << std::endl;

    while (!q.empty()) {
        size_t x = q.front();
        q.pop();
//        std::cout << std::endl << "x: " << x << std::endl;

        if (!used[x] && !marked[x]) {
            used[x] = true;
            marked[x] = true;
//            std::cout << "answer: " << g->getNode(x) << " + " << answer << std::endl;
            answer += g->getNode(x);
        }

        for (size_t y = 0; y < g->getSize(); y++) {
//            std::cout << "lnk[" << x << ", " << y << "]: " << g->getLink(y, x) << " | " << g->getLink(x, y) << std::endl;
            if (g->getLink(x, y) || g->getLink(y, x)) {
//                std::cout << "marked[" << y << "]: " << (marked[y] ? "+" : "-") << std::endl;
                if (!marked[y]) {
//                    std::cout << "y: " << y << std::endl;
                    marked[y] = used[x];
                    q.push(y);
                }
            }
        }
    }

//    std::cout << "answer: " << answer << std::endl;
    return answer;
}

size_t GraphWorker::findMaxNodesArray() {
    size_t answer = 0, node;
//    std::cout << std::endl;
    for (size_t i = 0; i < g->getSize(); i++) {
        size_t new_ = findMaxNodesArrayFromNode(i);
//        std::cout << i << ": " << new_ << std::endl;
        answer = std::max(answer, new_);
        if (new_ == answer) {
            node = i;
        }
    }
//    std::cout << "(" << node << ") ";

    return answer;
}


