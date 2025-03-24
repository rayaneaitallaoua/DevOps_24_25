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
 * @class Mapper
 * @brief Effectue le mapping de séquences (reads) sur un génome indexé avec des k-mers.
 *
 * Cette classe gère l'importation du génome de référence, le chargement de reads FASTA/FASTQ,
 * leur nettoyage, la recherche de leurs k-mers dans l'index, et l'affichage des positions d'alignement.
 */
class Mapper {
public:
    /**
     * @brief Constructeur
     * @param k Taille des k-mers
     * @param min_hits Seuil minimum d'occurrences pour valider un mapping
     */
    Mapper(int k, int min_hits);

    /**
     * @brief Charge le génome de référence à partir d'un fichier FASTA et construit l'index
     * @param filename Chemin vers le fichier FASTA du génome
     */
    void loadReference(const std::string& filename);

    /**
     * @brief Charge tous les fichiers de reads FASTA/FASTQ valides dans un dossier donné
     * @param dirPath Chemin vers le dossier contenant les fichiers de reads
     */
    void loadReadsFromDirectory(const std::string& dirPath);

    /**
     * @brief Mappe les reads valides sur le génome de référence à l'aide de l'index de k-mers
     */
    void mapReads();

    /**
     * @brief Affiche les résultats du mapping (positions et brin pour chaque read)
     */
    void printMappings() const;

    /**
     * @brief Accès direct à l'index pour interrogation externe (ex: k-mer à une position)
     * @return Une référence vers l'objet KmerIndex utilisé
     */
    KmerIndex& getGenomeIndex();

private:
    int k; /**< Taille des k-mers */
    int min_hits; /**< Seuil minimum de positions pour considérer un read mappé */
    KmerIndex genomeIndex; /**< Index de k-mers construit à partir du génome */
    std::vector<Sequence> reads; /**< Ensemble des reads valides chargés */
    std::unordered_map<std::string, std::vector<int>> mappings; /**< Positions de mapping par ID de read */
    std::unordered_map<std::string, std::string> strandInfo; /**< Brin associé au mapping (+, -, NA) */
};

#endif
