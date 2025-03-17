#include "ReadFasta.h"
#include "ReadFastq.h"

int main() {
    std::string fasta_file = "example.fasta";
    std::string fastq_file = "example.fastq";

    // Read and print FASTA sequences
    ReadFasta fastaReader(fasta_file);
    fastaReader.load();
    std::cout << "=== FASTA Sequences ===\n";
    fastaReader.printSequences();

    // Read and print FASTQ reads
    ReadFastq fastqReader(fastq_file);
    fastqReader.load();
    std::cout << "\n=== FASTQ Reads ===\n";
    fastqReader.printReads();

    return 0;
}