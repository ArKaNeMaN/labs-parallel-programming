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

size_t GraphWorker::findMaxNodesArray() {

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    world_size--;

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank == world_size) {
//        std::cout << "[" << world_size << "] findMaxNodesArray" << std::endl;

        size_t answer = 0;
        for (int i = 0; i < world_rank; i++) {
            size_t val;
//            std::cout << "[" << world_size << "] wait recv from " << i << std::endl;
            MPI_Recv(&val, 1, MPI_UNSIGNED_LONG_LONG, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//            std::cout << "[" << world_size << "] recv " << val << " from " << i;
            if (val > answer) {
                answer = val;
            }
        }

        // Чтобы процессы не летели вперёд
        for (int i = 0; i < world_rank; i++) {
            MPI_Send(&answer, 1, MPI_UNSIGNED_LONG_LONG, i, 0, MPI_COMM_WORLD);
        }

        return answer;
    }
//    std::cout << "[" << world_rank << "] findMaxNodesArray" << std::endl;

    size_t count, from, to;
    count = g->getSize() / world_size;
    from = count * world_rank;
    to = from + count;
    if (world_rank == 0) {
        to += g->getSize() % count;
    }

//    std::cout << "[" << world_rank << "] count = " << count << ", from = " << from << ", to = " << to << std::endl;

    size_t val = 0;
    for (size_t i = from; i < to; i++) {
        val = std::max(findMaxNodesArrayFromNode(i), val);
//        std::cout << "[" << world_rank << "] val = " << val << std::endl;
    }

//    std::cout << "[" << world_rank << "] val = " << val << std::endl;
    MPI_Send(&val, 1, MPI_UNSIGNED_LONG_LONG, world_size, 0, MPI_COMM_WORLD);

    MPI_Recv(&val, 1, MPI_UNSIGNED_LONG_LONG, world_size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    return 0;
}


