/**
 * @file Mapper.hpp
 * @brief Déclaration de la classe Mapper pour le mapping de reads sur un génome de référence.
 */

#ifndef MAPPER_HPP
#define MAPPER_HPP

#include "KmerIndex.hpp"
#include "Sequence.hpp"
#include <vector>
#include <unordered_map>
#include <string>

/**
 * @struct MappingResult
 * @brief Contient les résultats d'analyse d'un read : position, brin, cohérence et variation potentielle.
 */
struct MappingResult {
    bool aligned = false;                          /**< Le read est-il aligné de façon cohérente ? */
    std::string strand = "NA";                    /**< Brin (+, -, NA) */
    int start_pos = -1;                            /**< Position de départ estimée */
    int end_pos = -1;                              /**< Position de fin estimée */
    std::vector<int> aligned_kmer_indices;         /**< Index des k-mers du read qui sont alignés */
    std::string variation = "none";               /**< Type de variation suspectée ("none", "mutation", "error") */
};

/**
 * @class Mapper
 * @brief Effectue le mapping de séquences (reads) sur un génome indexé avec des k-mers.
 *
 * Cette classe gère l'importation du génome de référence, le chargement de reads FASTA/FASTQ,
 * leur nettoyage, la recherche de leurs k-mers dans l'index, et l'affichage des positions d'alignement.
 */
class Mapper {
public:
    Mapper(int k, int min_hits);

    void loadReference(const std::string& filename);
    void loadReadsFromDirectory(const std::string& dirPath);
    void mapReads();
    void printMappings() const;

    /**
     * @brief Analyse fine d'un read : positionnement de tous ses k-mers et diagnostic de variation
     * @param read Le read à analyser
     * @return Un objet MappingResult contenant les données d'interprétation
     */
    MappingResult analyzeRead(const Sequence& read);

    KmerIndex& getGenomeIndex();

private:
    int k;
    int min_hits;
    KmerIndex genomeIndex;
    std::vector<Sequence> reads;
    std::unordered_map<std::string, std::vector<int>> mappings;
    std::unordered_map<std::string, std::string> strandInfo;
};

#endif