// #include "ReadFasta.hpp"
// #include "ReadFastq.hpp"
// #include <iostream>
#include "Mapper.hpp"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <reference.fasta> <reads.fasta/fastq> <is_fastq (0/1)>\n";
        return 1;
    }

    std::string ref_file = argv[1];
    std::string reads_file = argv[2];
    bool isFastq = (std::stoi(argv[3]) == 1);

    int k = 5;  // Choisir une valeur raisonnable de k
    Mapper mapper(k);

    std::cout << "Loading reference genome...\n";
    mapper.loadReference(ref_file);

    std::cout << "Loading reads...\n";
    mapper.loadReads(reads_file, isFastq);

    std::cout << "Mapping reads...\n";
    mapper.mapReads();

    std::cout << "Mapping results:\n";
    mapper.printMappings();

    return 0;
}