#include "ReadFastq.h"

ReadFastq::ReadFastq(const std::string& filename) : filename(filename) {}

void ReadFastq::load() {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    std::string id, sequence, quality, line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        // Entry must start with '@'
        if (line[0] != '@') {
            std::cerr << "Error: Malformed FASTQ entry. Expected '@'. Sequence ignored.\n";
            continue;
        }

        id = line.substr(1);
        if (!std::getline(file, sequence) || sequence.empty()) {
            std::cerr << "Error: Missing sequence for " << id << ". Sequence ignored.\n";
            continue;
        }

        if (!std::getline(file, line) || line[0] != '+') {
            std::cerr << "Error: Missing '+' separator for " << id << ". Sequence ignored.\n";
            continue;
        }

        if (!std::getline(file, quality) || quality.empty()) {
            std::cerr << "Error: Missing quality string for " << id << ". Sequence ignored.\n";
            continue;
        }

        if (sequence.length() != quality.length()) {
            std::cerr << "Error: Quality length does not match sequence length for " << id << ". Sequence ignored.\n";
            continue;
        }

        reads.emplace_back(id, sequence, quality);
    }
}

void ReadFastq::printReads() const {
    for (const auto& read : reads) {
        read.print();
    }
}