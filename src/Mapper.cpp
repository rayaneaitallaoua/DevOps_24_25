#include "Mapper.hpp"
#include "ReadFasta.hpp"
#include "ReadFastq.hpp"
#include "Utils.hpp"
#include <iostream>

Mapper::Mapper(int k, int min_hits) : k(k), min_hits(min_hits), genomeIndex(k) {}

// Charge et indexe le génome de référence depuis un fichier FASTA
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

// Charge les reads depuis un dossier en détectant automatiquement s'ils sont en FASTA ou FASTQ
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

// Effectue le mapping des reads sur le génome de référence
void Mapper::mapReads() {
    for (const auto& read : reads) {
        std::string strand; // contiendra "+" ou "-" ou "NA"

        // On cherche le k-mer dans les deux brins
        std::vector<int> positions = genomeIndex.searchKmerWithStrand(
            read.getSequence().substr(0, k), strand);

        if (!positions.empty() && positions.size() >= min_hits) {
            mappings[read.getId()] = positions;
            strandInfo[read.getId()] = strand;
        } else {
            mappings[read.getId()] = {-1};
            strandInfo[read.getId()] = "NA";
        }
    }
}

// Affiche les résultats du mapping
void Mapper::printMappings() const {
    for (const auto& [read_id, positions] : mappings) {
        std::cout << "Read " << read_id
                  << " mapped on strand " << strandInfo.at(read_id)
                  << " at positions: ";

        for (int pos : positions) {
            if (pos == -1) std::cout << "Not found";
            else std::cout << pos << " ";
        }
        std::cout << "\n";
    }
}