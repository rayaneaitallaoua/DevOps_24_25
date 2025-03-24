#include "Mapper.hpp"
#include "ReadFasta.hpp"
#include "ReadFastq.hpp"
#include "Utils.hpp"
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

void Mapper::loadReadsFromDirectory(const std::string& dirPath) {
    std::vector<std::string> files = listFilesInDirectory(dirPath);

    for (const auto& file : files) {
        std::string format = detectFileFormat(file);

        if (format == "fasta") {
            ReadFasta fastaReader(file);
            fastaReader.load();
            std::vector<Sequence> validReads = fastaReader.getSequences();

            if (!validReads.empty()) {
                reads.insert(reads.end(), validReads.begin(), validReads.end());
            } else {
                std::cerr << "Warning: No valid reads in " << file << ". Ignored.\n";
            }

        } else if (format == "fastq") {
            ReadFastq fastqReader(file);
            fastqReader.load();
            std::vector<Sequence> validReads = fastqReader.getReads();

            if (!validReads.empty()) {
                reads.insert(reads.end(), validReads.begin(), validReads.end());
            } else {
                std::cerr << "Warning: No valid reads in " << file << ". Ignored.\n";
            }

        } else {
            std::cerr << "Error: Unknown format for " << file << ". Ignored.\n";
        }
    }
}

void Mapper::mapReads() {
    for (const auto& read : reads) {
        std::vector<int> positions = genomeIndex.searchKmer(read.getSequence().substr(0, k));

        if (!positions.empty()) {
            mappings[read.getId()] = positions;
        } else {
            mappings[read.getId()] = {-1};
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