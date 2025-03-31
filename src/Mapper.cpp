/**
 * @file Mapper.cpp
 * @brief Implémentation de la classe Mapper pour le mapping de reads sur un génome de référence.
 */

#include "Mapper.hpp"
#include "ReadFasta.hpp"
#include "ReadFastq.hpp"
#include "Utils.hpp"
#include <iostream>
#include <unordered_map>
#include <map>
#include <algorithm>

/**
 * @brief Constructeur de la classe Mapper
 * @param k taille des k-mers à utiliser pour l'indexation et le mapping
 * @param min_hits seuil minimum de k-mers alignés pour considérer un read mappé
 */
Mapper::Mapper(int k, int min_hits) : k(k), min_hits(min_hits), genomeIndex(k) {}

/**
 * @brief Charge le génome de référence depuis un fichier FASTA et l'indexe avec les k-mers
 * @param filename chemin vers le fichier FASTA contenant le génome
 */
void Mapper::loadReference(const std::string& filename) {
    ReadFasta fastaReader(filename);
    fastaReader.load();

    std::cout << "Indexing genome...\n";
    std::string genome;
    for (const auto& seq : fastaReader.getSequences()) {
        genome += seq.getSequence();
    }
    genomeIndex.indexGenome(genome);
}

/**
 * @brief Charge et valide tous les reads (FASTA ou FASTQ) présents dans un dossier
 * @param dirPath chemin vers le dossier contenant les fichiers de reads
 */
void Mapper::loadReadsFromDirectory(const std::string& dirPath) {
    std::vector<std::string> files = listFilesInDirectory(dirPath);

    for (const auto& file : files) {
        std::string format = detectFileFormat(file);

        if (format == "fasta") {
            ReadFasta fastaReader(file);
            fastaReader.load();
            std::vector<Sequence> validReads = fastaReader.getSequences();
            if (!validReads.empty()) {
                reads.insert(reads.end(), validReads.begin(), validReads.end());
            } else {
                std::cerr << "Warning: No valid reads in " << file << ". Ignored.\n";
            }

        } else if (format == "fastq") {
            ReadFastq fastqReader(file);
            fastqReader.load();
            std::vector<Sequence> validReads = fastqReader.getReads();
            if (!validReads.empty()) {
                reads.insert(reads.end(), validReads.begin(), validReads.end());
            } else {
                std::cerr << "Warning: No valid reads in " << file << ". Ignored.\n";
            }

        } else {
            std::cerr << "Error: Unknown format for " << file << ". Ignored.\n";
        }
    }
}

/**
 * @brief Effectue le mapping de tous les reads valides sur le génome indexé
 */
void Mapper::mapReads() {
    for (const auto& read : reads) {
        MappingResult result = analyzeRead(read);
        mappings[read.getId()] = {result.start_pos};
        strandInfo[read.getId()] = result.strand;
        variations[read.getId()] = result.variation;
    }
}

/**
 * @brief Affiche les résultats du mapping pour chaque read (position, brin, variation)
 */
void Mapper::printMappings() const {
    for (const auto& [read_id, positions] : mappings) {
        std::cout << "Read " << read_id
                  << " mapped on strand " << strandInfo.at(read_id)
                  << " at positions: ";

        for (int pos : positions) {
            if (pos == -1) std::cout << "Not found";
            else std::cout << pos << " ";
        }

        std::cout << " | Variation: " << variations.at(read_id) << "\n";
    }
}

/**
 * @brief Donne accès à l'objet KmerIndex utilisé pour indexer le génome
 * @return référence vers l'index des k-mers
 */
KmerIndex& Mapper::getGenomeIndex() {
    return genomeIndex;
}

/**
 * @brief Analyse un read en examinant les positions de tous ses k-mers sur le génome
 *
 * Pour chaque k-mer du read :
 * - recherche dans l'index (ou reverse complement)
 * - vote pour la position estimée de départ du read
 * - identification du brin principal
 * - comptage du nombre de k-mers alignés
 *
 * Une variation est inférée selon le nombre de k-mers alignés :
 * - "none" si tous les k-mers sont alignés
 * - "mutation" si certains k-mers manquent
 * - "error" si trop peu sont alignés
 *
 * @param read objet Sequence à analyser
 * @return un MappingResult contenant toutes les infos d'alignement
 */
MappingResult Mapper::analyzeRead(const Sequence& read) {
    MappingResult result;
    std::string seq = read.getSequence();
    int read_length = seq.length();
    if (read_length < k) return result;

    std::map<int, int> positionVotes;
    std::string globalStrand = "";
    int consistentHits = 0;

    for (int i = 0; i <= read_length - k; ++i) {
        std::string kmer = seq.substr(i, k);
        std::string strand;
        std::vector<int> positions = genomeIndex.searchKmerWithStrand(kmer, strand);

        if (!positions.empty()) {
            for (int pos : positions) {
                int estimatedStart = pos - i;
                positionVotes[estimatedStart]++;
            }
            if (globalStrand.empty()) globalStrand = strand;
            else if (globalStrand != strand) globalStrand = "NA";
            result.aligned_kmer_indices.push_back(i);
            ++consistentHits;
        }
    }

    if (!positionVotes.empty()) {
        auto best = std::max_element(positionVotes.begin(), positionVotes.end(),
            [](const auto& a, const auto& b) {
                return a.second < b.second;
            });
        result.start_pos = best->first;
        result.end_pos = result.start_pos + read_length - 1;
        result.strand = globalStrand;
        result.aligned = true;

        int totalKmers = read_length - k + 1;
        int alignedCount = result.aligned_kmer_indices.size();

        if (alignedCount < totalKmers * 0.5) {
            result.variation = "error";
        } else if (alignedCount < totalKmers) {
            result.variation = "mutation";
        }
    }

    return result;
}