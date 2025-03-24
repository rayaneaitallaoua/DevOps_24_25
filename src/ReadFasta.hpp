#ifndef READFASTA_HPP
#define READFASTA_HPP

#include "Sequence.hpp"
#include <vector>
#include <fstream>
#include <string>

class ReadFasta {
public:
    ReadFasta(const std::string& filename);
    void load();
    void printSequences() const;

private:
    std::string filename;
    std::vector<Sequence> sequences;
};

#endif