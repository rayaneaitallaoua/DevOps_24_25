#include "Mapper.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <reference.fasta> <reads_directory>\n";
        return 1;
    }

    std::string ref_file = argv[1];
    std::string reads_dir = argv[2];

    int k = 5;  // Taille du k-mer
    Mapper mapper(k);

    std::cout << "Loading reference genome...\n";
    mapper.loadReference(ref_file);

    std::cout << "Loading reads from directory...\n";
    mapper.loadReadsFromDirectory(reads_dir);

    std::cout << "Mapping reads...\n";
    mapper.mapReads();

    std::cout << "Mapping results:\n";
    mapper.printMappings();

    return 0;
}