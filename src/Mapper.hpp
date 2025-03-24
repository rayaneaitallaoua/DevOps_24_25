#ifndef MAPPER_HPP
#define MAPPER_HPP

#include "KmerIndex.hpp"
#include "Sequence.hpp"
#include <vector>
#include <unordered_map>

class Mapper {
public:
    Mapper(int k, int min_hits);
    void loadReference(const std::string& filename);
    void loadReadsFromDirectory(const std::string& dirPath);
    void mapReads();
    void printMappings() const;
    std::unordered_map<std::string, std::string> strandInfo;

private:
    int k;  // Taille des k-mers
    int min_hits; // Seuil minimum de hits pour considérer un read comme mappé
    KmerIndex genomeIndex;  // Index des k-mers du génome
    std::vector<Sequence> reads;  // Reads valides
    std::unordered_map<std::string, std::vector<int>> mappings;  // Stockage des résultats du mapping
};

#endif