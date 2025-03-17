#include "Sequence.hpp"

Sequence::Sequence(const std::string& id, const std::string& seq, const std::string& qual) 
    : id(id), sequence(seq), quality(qual) {}

std::string Sequence::getId() const {
    return id;
}

std::string Sequence::getSequence() const {
    return sequence;
}

std::string Sequence::getQuality() const {
    return quality;
}

bool Sequence::hasQuality() const {
    return !quality.empty();
}

void Sequence::print() const {
    std::cout << ">" << id << "\n" << sequence;
    if (!quality.empty()) {
        std::cout << "\n+\n" << quality;
    }
    std::cout << "\n";
}