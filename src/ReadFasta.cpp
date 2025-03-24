#include "ReadFasta.hpp"
#include <cctype>

ReadFasta::ReadFasta(const std::string& filename) : filename(filename) {}

void ReadFasta::load() {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    std::string line, seq_id, sequence;
    bool valid = true;  // Flag to check if sequence is valid

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        if (line[0] == '>') {
            // Store previous sequence if valid
            if (!seq_id.empty()) {
                if (valid) {
                    sequences.emplace_back(seq_id, sequence);
                } else {
                    std::cerr << "Warning: Non-ACGT character detected in sequence " << seq_id << ". Sequence was ignored.\n";
                }
            }

            seq_id = line.substr(1);
            sequence.clear();
            valid = true; // Reset flag for new sequence
        } else {
            // If we haven't seen a '>' yet, this is an error
            if (seq_id.empty()) {
                std::cerr << "Error: Malformed FASTA file. Missing '>' before sequence. Sequence ignored.\n";
                continue;
            }

            // Check for non-ACGT characters
            for (char c : line) {
                if (c != 'A' && c != 'C' && c != 'G' && c != 'T') {
                    valid = false;
                }
            }
            sequence += line;
        }
    }

    // Store last sequence if valid
    if (!seq_id.empty()) {
        if (valid) {
            sequences.emplace_back(seq_id, sequence);
        } else {
            std::cerr << "Warning: Non-ACGT character detected in sequence " << seq_id << ". Sequence was ignored.\n";
        }
    }
}

void ReadFasta::printSequences() const {
    for (const auto& seq : sequences) {
        seq.print();
    }
}

std::vector<Sequence> ReadFasta::getSequences() const {
    return sequences;
}