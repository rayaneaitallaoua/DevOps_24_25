#ifndef MAPPER_HPP
#define MAPPER_HPP

#include "KmerIndex.hpp"
#include "Sequence.hpp"
#include <vector>

class Mapper {
public:
    Mapper(int k);
    void loadReference(const std::string& filename);
    void loadReads(const std::string& filename, bool isFastq);
    void mapReads();
    void printMappings() const;

private:
    int k;
    KmerIndex genomeIndex;
    std::vector<Sequence> reads;
    std::unordered_map<std::string, std::vector<int>> mappings;
};

#endif