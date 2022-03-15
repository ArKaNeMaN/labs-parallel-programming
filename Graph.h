//
// Created by arkan on 16.02.2022.
//

#ifndef CPP_FINDMAXGRAPHPART_GRAPH_H
#define CPP_FINDMAXGRAPHPART_GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

typedef long int weight_t;
typedef std::vector<weight_t> nodes_vec_t;
typedef std::vector<nodes_vec_t> graph_t;

class Graph {
private:
    size_t size;
    graph_t g;
    nodes_vec_t nodes;
    bool directed;

public:
    explicit Graph(size_t, bool = false);

    void setNode(size_t);
    void setNode(size_t, weight_t);
    weight_t getNode(size_t);

    void setLink(size_t, size_t);
    void setLink(size_t, size_t, weight_t);
    weight_t getLink(size_t, size_t);
    bool hasLink(size_t, size_t);

    [[nodiscard]]
    size_t getSize() const;

    static Graph* readFromFile(const std::string&);
    Graph* saveToFile(const std::string &filePath, bool pretty = false);
};

#endif //CPP_FINDMAXGRAPHPART_GRAPH_H
