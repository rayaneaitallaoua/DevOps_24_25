#include "Mapper.hpp"
#include "ReadFasta.hpp"
#include "ReadFastq.hpp"
#include <iostream>

Mapper::Mapper(int k) : k(k), genomeIndex(k) {}

void Mapper::loadReference(const std::string& filename) {
    ReadFasta fastaReader(filename);
    fastaReader.load();
    std::cout << "Indexing genome...\n";

    std::string genome;
    for (const auto& seq : fastaReader.getSequences()) {
        genome += seq.getSequence();
    }

    genomeIndex.indexGenome(genome);
}

void Mapper::loadReads(const std::string& filename, bool isFastq) {
    if (isFastq) {
        ReadFastq fastqReader(filename);
        fastqReader.load();
        reads = fastqReader.getReads();
    } else {
        ReadFasta fastaReader(filename);
        fastaReader.load();
        reads = fastaReader.getSequences();
    }
}

void Mapper::mapReads() {
    for (const auto& read : reads) {
        std::vector<int> positions = genomeIndex.searchKmer(read.getSequence().substr(0, k));
        if (!positions.empty()) {
            mappings[read.getId()] = positions;
        } else {
            mappings[read.getId()] = {-1}; // -1 = non trouvé
        }
    }
}

void Mapper::printMappings() const {
    for (const auto& [read_id, positions] : mappings) {
        std::cout << "Read " << read_id << " mapped at positions: ";
        for (int pos : positions) {
            if (pos == -1) std::cout << "Not found";
            else std::cout << pos << " ";
        }
        std::cout << "\n";
    }
}