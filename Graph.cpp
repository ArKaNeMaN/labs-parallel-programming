//
// Created by arkan on 16.02.2022.
//

#include "Graph.h"
Graph::Graph(size_t size, bool directed) {
    this->directed = directed;

    this->size = size;
    g.resize(size);
    nodes.resize(size);

    for (int i = 0; i < size; i++) {
        g[i].resize(size);
        nodes[i] = 0;

        for (int j = 0; j < size; j++) {
            g[i][j] = 0;
        }
    }
}

void Graph::setNode(size_t node, weight_t w) {
    nodes[node] = w;
}

void Graph::setNode(size_t node) {
    setNode(node, 1);
}

weight_t Graph::getNode(size_t node) {
    return nodes[node];
}

void Graph::setLink(size_t x, size_t y) {
    setLink(x, y, 1);
}

void Graph::setLink(size_t x, size_t y, weight_t w) {
    g[x][y] = w;
    if (directed) {
        g[y][x] = w;
    }
}

weight_t Graph::getLink(size_t x, size_t y) {
    return g[x][y];
}

bool Graph::hasLink(size_t x, size_t y) {
    return getLink(x, y) > 0;
}

size_t Graph::getSize() const {
    return size;
}

Graph* Graph::readFromFile(const std::string& filePath) {
    std::ifstream fs;
    fs.open(filePath.c_str(), std::_S_in);

    if (!fs.is_open()) {
        printf("Can`t open file '%s'.", filePath.c_str());
        return nullptr;
    }

    size_t size;
    bool isStartsFromZero, isDirected;
    fs >> isDirected >> isStartsFromZero >> size;

    auto* g = new Graph(size, isDirected);

    for (size_t i = 0; i < size; i++) {
        weight_t w;
        fs >> w;
        g->setNode(i, w);
    }

    while (!fs.eof()) {
        size_t x, y;
        weight_t w;
        fs >> x >> y >> w;
        if (!isStartsFromZero) {
            x--;
            y--;
        }

        g->setLink(x, y, w);
    }
    fs.close();

    return g;
}

Graph* Graph::saveToFile(const std::string& filePath, const bool pretty) {
    const auto delimiter = ' ';

    std::ofstream fs;
    fs.open(filePath.c_str(), std::_S_out);

    if (!fs.is_open()) {
        printf("Can`t open file '%s'.", filePath.c_str());
        return nullptr;
    }

    fs << delimiter << directed << delimiter << 1 << delimiter;
    if (pretty) {
        fs << std::endl;
    }

    fs << size << delimiter;
    if (pretty) {
        fs << std::endl << std::endl;
    }

    for (size_t i = 0; i < size; i++) {
        fs << getNode(i) << delimiter;
    }
    if (pretty) {
        fs << std::endl << std::endl;
    }

    for (size_t i = 0; i < size; i++) {
        for (size_t j = directed ? 0 : i; j < size; j++) {
            weight_t w = getLink(i, j);
            if (w > 0) {
                fs  << i << delimiter << j << delimiter << w << delimiter;
                if (pretty) {
                    fs << std::endl;
                }
            }
        }
    }

    fs.close();

    return this;
}
