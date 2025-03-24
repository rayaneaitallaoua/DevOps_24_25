#ifndef KMERINDEX_HPP
#define KMERINDEX_HPP

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

class KmerIndex {
public:
    KmerIndex(int k);
    void indexGenome(const std::string& genome);
    std::vector<int> searchKmer(const std::string& kmer) const;
    void printIndex() const;

private:
    int k;
    std::unordered_map<std::string, std::vector<int>> index;
};

#endif