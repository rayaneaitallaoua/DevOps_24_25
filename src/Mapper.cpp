/**
 * @file Mapper.cpp
 * @brief Implémentation de la classe Mapper pour le mapping de reads sur un génome de référence.
 */

#include "Mapper.hpp"
#include "ReadFasta.hpp"
#include "ReadFastq.hpp"
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <numeric>

Mapper::Mapper(int k, int min_hits) : k(k), min_hits(min_hits), genomeIndex(k) {}

std::vector<Sequence> Mapper::getReads() const {
    return reads;
}

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

void Mapper::loadReadsFromDirectory(const std::string& dirPath) {
    std::vector<std::string> files = listFilesInDirectory(dirPath);

    for (const auto& file : files) {
        std::string format = detectFileFormat(file);
        std::cout << "Fichier : " << file << " | Format détecté : " << format << "\n";

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

void Mapper::mapReads() {
    for (const auto& read : reads) {
        MappingResult result = analyzeRead(read);
        mappings[read.getId()] = {result.start_pos};
        strandInfo[read.getId()] = result.strand;
        variations[read.getId()] = result.variation;
        mappingResults[read.getId()] = result;
    }
}

void Mapper::exportMappingsToCSV(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Error: Cannot open output file " << filename << "\n";
        return;
    }

    // Écriture des paramètres d'analyse
    out << "k-mer size," << k << "\n";
    out << "minimum hits," << min_hits << "\n\n";

    // Statistiques globales
    int total_reads = static_cast<int>(reads.size());
    int mapped_reads = 0;
    std::vector<int> qualities_all, qualities_mapped;

    for (const auto& read : reads) {

        const std::string& id = read.getId();
        if (mappingResults.find(id) != mappingResults.end() && mappingResults.at(id).aligned) {
            mapped_reads++;
            if (!read.getQuality().empty()) {
                qualities_mapped.push_back(medianQuality(read.getQuality()));
            }
        }
        if (!read.getQuality().empty()) {
            qualities_all.push_back(medianQuality(read.getQuality()));
        }
    }

    int unmapped_reads = total_reads - mapped_reads;
    double mapped_percent = total_reads > 0 ? 100.0 * mapped_reads / total_reads : 0.0;
    double unmapped_percent = total_reads > 0 ? 100.0 * unmapped_reads / total_reads : 0.0;

    out << "total reads," << total_reads << "\n";
    out << "mapped reads," << mapped_reads << "," << mapped_percent << "%\n";
    out << "unmapped reads," << unmapped_reads << "," << unmapped_percent << "%\n";

    // Statistiques de qualité si FASTQ
    if (!qualities_all.empty()) {
        std::sort(qualities_all.begin(), qualities_all.end());
        std::sort(qualities_mapped.begin(), qualities_mapped.end());

        int median_all = qualities_all[qualities_all.size() / 2];
        int median_mapped = qualities_mapped.empty() ? -1 : qualities_mapped[qualities_mapped.size() / 2];
        double mean_mapped = qualities_mapped.empty() ? 0.0 :
            std::accumulate(qualities_mapped.begin(), qualities_mapped.end(), 0.0) / qualities_mapped.size();

        out << "median read quality (all reads)," << median_all << "\n";
        out << "median read quality (mapped reads)," << median_mapped << "\n";
        out << "mean read quality (mapped reads)," << mean_mapped << "\n";
    }

    out << "\n";

    // En-tête du CSV
    out << "read_id,sequence,alignment_percentage,start_position,variation_type,variation_position\n";

    for (const auto& read : reads) {
        const std::string& id = read.getId();
        const std::string& seq = read.getSequence();
        const MappingResult& result = mappingResults.at(id);

        int total_kmers = static_cast<int>(seq.length()) - k + 1;
        int aligned_kmers = static_cast<int>(result.aligned_kmer_indices.size());
        double alignment_percentage = (total_kmers > 0) ? 100.0 * aligned_kmers / total_kmers : 0.0;

        int variation_position = -1;
        for (int i = 0; i <= static_cast<int>(seq.length()) - k; ++i) {
            if (std::find(result.aligned_kmer_indices.begin(), result.aligned_kmer_indices.end(), i) == result.aligned_kmer_indices.end()) {
                variation_position = i;
                break;
            }
        }

        out << id << ","
            << seq << ","
            << alignment_percentage << ","
            << result.start_pos << ","
            << result.variation << ","
            << variation_position << "\n";
    }

    out.close();
}

KmerIndex& Mapper::getGenomeIndex() {
    return genomeIndex;
}

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