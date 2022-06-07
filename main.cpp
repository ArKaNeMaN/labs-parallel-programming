#include <iostream>
#include <mpi.h>
#include "Graph.h"
#include "GraphWorker.h"

int mpi_rank;
int mpi_size;

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
        if (mpi_rank == mpi_size - 1) {
            std::cout << size << ' ' << seed << ' ' << std::endl;
        }

        size_t answer;
        time_t t = time(nullptr);
        answer = gw->findMaxNodesArray();
        time_t t2 = time(nullptr);

        delete gw->getGraph();
        delete gw;

        if (mpi_rank == mpi_size - 1) {
            fso << size << ' ' << seed << ' ' << " (ans: " << answer << ", time: " << difftime(t2, t) << ')' << std::endl;
            std::cout << " (ans: " << answer << ", time: " << difftime(t2, t) << ')' << std::endl;
        }
    }

    fsi.close();
    fso.close();
}

int main() {
    MPI_Init(nullptr, nullptr);

    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

    if (mpi_rank == mpi_size - 1) {
        std::cout << "mpi (4 cores):" << std::endl;
    }
    runFromSeeds();

    MPI_Finalize();

    return 0;
}
