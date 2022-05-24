#include <iostream>
#include <mpi.h>
#include "Graph.h"
#include "GraphWorker.h"

int mpi_rank;

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
        if (mpi_rank == 0) {
            std::cout << size << ' ' << seed << ' ';
        }

        size_t answer;
        double t = MPI_Wtime();
        answer = gw->findMaxNodesArray();
        double t2 = MPI_Wtime();

        delete gw->getGraph();
        delete gw;

        if (mpi_rank == 0) {
            fso << size << ' ' << seed << ' ' << " (ans: " << answer << ", time: " << t2 - t << ')' << std::endl;
            std::cout << " (ans: " << answer << ", time: " << t2 - t << ')' << std::endl;
        }
    }

    fsi.close();
    fso.close();
}

int main() {
    MPI_Init(nullptr, nullptr);

    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
//
//    if (mpi_rank == 0) {
//        std::cout << "mpi (4 cores):" << std::endl;
//    }
//    runFromSeeds();

    if (mpi_rank == 0) {
        std::ifstream fsi;
        fsi.open("../tests/seeds.txt", std::_S_in);
        size_t size;
        int seed;
        fsi >> size >> seed;
        std::cout << size << ' ' << seed << std::endl;
        fsi.close();
    } else {
        std::cout << "kek" << std::endl;
    }


    MPI_Finalize();

    return 0;
}
