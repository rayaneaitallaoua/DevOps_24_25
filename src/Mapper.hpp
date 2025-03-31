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
    std::string strand = "NA";                     /**< Brin détecté pour l'alignement : '+', '-' ou 'NA' */
    int start_pos = -1;                            /**< Position de départ estimée du read sur le génome */
    int end_pos = -1;                              /**< Position de fin estimée du read sur le génome */
    std::vector<int> aligned_kmer_indices;         /**< Indices des k-mers du read qui ont été trouvés dans l'index */
    std::string variation = "none";                /**< Type de variation détectée : 'none', 'mutation', ou 'error' */
};

/**
 * @class Mapper
 * @brief Effectue le mapping de séquences (reads) sur un génome indexé avec des k-mers.
 *
 * Cette classe gère :
 * - le chargement du génome de référence à partir d'un fichier FASTA
 * - l'indexation du génome avec des k-mers
 * - la lecture et validation de reads (FASTA ou FASTQ)
 * - l'analyse de l'alignement de chaque read via ses k-mers
 * - la détection de variations éventuelles (mutations, erreurs)
 * - l'affichage ou l'export des résultats
 */
class Mapper {
public:
    /**
     * @brief Constructeur de la classe Mapper
     * @param k taille des k-mers à utiliser pour l'indexation
     * @param min_hits nombre minimum de k-mers requis pour considérer un alignement comme valide
     */
    Mapper(int k, int min_hits);

    /**
     * @brief Charge un fichier FASTA et indexe le génome pour les k-mers.
     * @param filename chemin vers le fichier FASTA du génome de référence
     */
    void loadReference(const std::string& filename);

    /**
     * @brief Charge tous les reads valides à partir d'un répertoire contenant des fichiers FASTA/FASTQ.
     * @param dirPath chemin vers le dossier contenant les fichiers de reads
     */
    void loadReadsFromDirectory(const std::string& dirPath);

    /**
     * @brief Effectue le mapping de tous les reads valides sur le génome indexé.
     */
    void mapReads();

    /**
     * @brief Analyse fine d'un read : positionnement de tous ses k-mers et diagnostic de variation.
     * @param read Le read à analyser
     * @return Un objet MappingResult contenant les données d'interprétation
     */
    MappingResult analyzeRead(const Sequence& read);

    /**
     * @brief Accès à l'index des k-mers du génome de référence.
     * @return Une référence vers l'objet KmerIndex utilisé
     */
    KmerIndex& getGenomeIndex();

    /**
     * @brief Exporte tous les résultats du mapping dans un fichier CSV.
     * Le fichier contient : paramètres, ID du read, séquence, pourcentage d'alignement,
     * position estimée, type de variation, position de la variation.
     * @param filename chemin du fichier CSV de sortie
     */
    void exportMappingsToCSV(const std::string& filename) const;

    /**
    * @brief Retourne la liste des reads chargés
    * @return Vecteur de reads
    */
    std::vector<Sequence> getReads() const;

private:
    int k;    /**< Taille des k-mers utilisés */
    int min_hits;  /**< Seuil de k-mers alignés requis pour valider un mapping */
    KmerIndex genomeIndex;  /**< Index k-mer construit à partir du génome de référence */
    std::vector<Sequence> reads;  /**< Reads valides extraits des fichiers FASTA/FASTQ */
    std::unordered_map<std::string, std::vector<int>> mappings;  /**< Positions de mapping pour chaque read */
    std::unordered_map<std::string, std::string> strandInfo;     /**< Brin détecté pour chaque read */
    std::unordered_map<std::string, std::string> variations;     /**< Type de variation détectée pour chaque read */
    std::unordered_map<std::string, MappingResult> mappingResults; /**< Résultats complets de l'analyse pour chaque read */
};

#endif