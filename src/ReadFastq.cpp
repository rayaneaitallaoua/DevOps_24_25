#include "ReadFastq.hpp"

ReadFastq::ReadFastq(const std::string& filename) : filename(filename) {}

void ReadFastq::load() {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::string id = line.substr(1);
        std::string sequence, quality;
        std::getline(file, sequence);
        std::getline(file, line); // Skip '+'
        std::getline(file, quality);
        reads.emplace_back(id, sequence, quality);
    }
}

void ReadFastq::printReads() const {
    for (const auto& read : reads) {
        read.print();
    }
}