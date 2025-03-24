#include "KmerIndex.hpp"
#include "Utils.hpp"
#include <iostream>

KmerIndex::KmerIndex(int k) : k(k) {}

void KmerIndex::indexGenome(const std::string& sequence) {
    genome = sequence;
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

std::string KmerIndex::getKmerAtPosition(int i) const {
    if (i >= 0 && i <= genome.size() - k) {
        return genome.substr(i, k); // extrait le k-mer à la position i
    }
    return ""; // si position invalide
}

std::vector<int> KmerIndex::searchKmerWithStrand(const std::string& kmer, std::string& strand) const {
    auto it = index.find(kmer);
    if (it != index.end()) {
        strand = "+"; // trouvé dans le sens direct
        return it->second;
    }

    // Chercher le brin complémentaire inversé
    std::string rc = reverseComplement(kmer);
    it = index.find(rc);
    if (it != index.end()) {
        strand = "-"; // trouvé sur le brin inverse
        return it->second;
    }

    strand = "NA"; // non trouvé
    return {};
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