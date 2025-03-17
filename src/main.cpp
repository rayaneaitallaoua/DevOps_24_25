#include "ReadFasta.h"
#include "ReadFastq.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <fasta_file> <fastq_file>\n";
        return 1;
    }

    std::string fasta_file = argv[1];
    std::string fastq_file = argv[2];

    // Read and print FASTA sequences
    ReadFasta fastaReader(fasta_file);
    fastaReader.load();
    std::cout << "\n=== FASTA Sequences ===\n";
    fastaReader.printSequences();

    // Read and print FASTQ reads
    ReadFastq fastqReader(fastq_file);
    fastqReader.load();
    std::cout << "\n=== FASTQ Reads ===\n";
    fastqReader.printReads();

    return 0;
}