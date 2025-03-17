#include "ReadFasta.h"

ReadFasta::ReadFasta(const std::string& filename) : filename(filename) {}

void ReadFasta::load() {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    std::string line, seq_id, sequence;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (line[0] == '>') {
            if (!seq_id.empty()) {
                sequences.emplace_back(seq_id, sequence);
                sequence.clear();
            }
            seq_id = line.substr(1);
        } else {
            sequence += line;
        }
    }
    if (!seq_id.empty()) sequences.emplace_back(seq_id, sequence);
}

void ReadFasta::printSequences() const {
    for (const auto& seq : sequences) {
        seq.print();
    }
}