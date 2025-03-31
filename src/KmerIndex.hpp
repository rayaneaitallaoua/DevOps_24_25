/**
 * @file KmerIndex.hpp
 * @brief Déclaration de la classe KmerIndex pour l'indexation de k-mers dans un génome.
 */

#ifndef KMERINDEX_HPP
#define KMERINDEX_HPP

#include <unordered_map>
#include <vector>
#include <string>

/**
 * @class KmerIndex
 * @brief Structure permettant d'indexer des mots de longueur fixe (k-mers) dans un texte génomique.
 *
 * Cette classe permet :
 * - d'indexer un génome pour retrouver rapidement les occurrences d'un k-mer,
 * - de rechercher un k-mer ou son brin complémentaire inversé,
 * - de récupérer le k-mer présent à une position donnée du texte.
 */
class KmerIndex {
public:
    /**
     * @brief Constructeur
     * @param k Taille des k-mers à indexer
     */
    KmerIndex(int k);

    /**
     * @brief Indexe tous les k-mers d'un génome donné
     * @param genome Séquence génomique à indexer
     */
    void indexGenome(const std::string& genome);

    /**
     * @brief Recherche un k-mer ou son brin complémentaire inversé
     * @param kmer Le k-mer à rechercher
     * @param strand Variable de sortie : "+", "-" ou "NA"
     * @return Vecteur de positions du k-mer trouvé
     */
    std::vector<int> searchKmerWithStrand(const std::string& kmer, std::string& strand) const;

    /**
     * @brief Récupère le k-mer présent à la position i dans le génome indexé
     * @param i Position dans le génome (0-based)
     * @return Le k-mer si i est valide, sinon une chaîne vide
     */
    std::string getKmerAtPosition(int i) const;

    /**
     * @brief Affiche tous les k-mers indexés avec leurs positions
     */
    void printIndex() const;

private:
    int k;  /**< Taille des k-mers */
    std::unordered_map<std::string, std::vector<int>> index; /**< Table d'indexation des k-mers */
    std::string genome; /**< Texte génomique complet utilisé pour l'indexation */
};

#endif
