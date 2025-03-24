#include "KmerIndex.hpp"

KmerIndex::KmerIndex(int k) : k(k) {}

void KmerIndex::indexGenome(const std::string& genome) {
    int genome_length = genome.length();
    for (int i = 0; i <= genome_length - k; i++) {
        std::string kmer = genome.substr(i, k);
        index[kmer].push_back(i);
    }
}

std::vector<int> KmerIndex::searchKmer(const std::string& kmer) const {
    auto it = index.find(kmer);
    if (it != index.end()) {
        return it->second;
    }
    return {};  // Retourne un vecteur vide si le k-mer n'est pas trouvé
}

void KmerIndex::printIndex() const {
    for (const auto& [kmer, positions] : index) {
        std::cout << kmer << " -> ";
        for (int pos : positions) {
            std::cout << pos << " ";
        }
        std::cout << "\n";
    }
}