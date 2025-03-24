/**
* @file ReadFastq.cpp
 * @brief Implémentation de la classe ReadFastq pour la lecture de fichiers FASTQ.
 */

#include "ReadFastq.hpp"
#include <fstream>
#include <iostream>

ReadFastq::ReadFastq(const std::string& filename) : filename(filename) {}

void ReadFastq::load() {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    std::string id, sequence, plus_line, quality;

    while (std::getline(file, id)) {
        if (id.empty()) continue;

        if (id[0] != '@') {
            std::cerr << "Error: Malformed FASTQ entry. Expected '@'. Sequence ignored." << std::endl;
            continue;
        }

        if (!std::getline(file, sequence) || sequence.empty()) {
            std::cerr << "Error: Missing sequence for " << id << ". Sequence ignored." << std::endl;
            continue;
        }

        if (!std::getline(file, plus_line) || plus_line[0] != '+') {
            std::cerr << "Error: Missing '+' separator for " << id << ". Sequence ignored." << std::endl;
            continue;
        }

        if (!std::getline(file, quality) || quality.empty()) {
            std::cerr << "Error: Missing quality string for " << id << ". Sequence ignored." << std::endl;
            continue;
        }

        if (sequence.length() != quality.length()) {
            std::cerr << "Error: Quality length does not match sequence length for " << id << ". Sequence ignored." << std::endl;
            continue;
        }

        reads.emplace_back(id.substr(1), sequence, quality);
    }
}

void ReadFastq::printReads() const {
    for (const auto& read : reads) {
        read.print();
    }
}

std::vector<Sequence> ReadFastq::getReads() const {
    return reads;
}
