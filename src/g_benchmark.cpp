#include <benchmark/benchmark.h>
#include "Mapper.hpp"
#include "ReadFasta.hpp"
#include <fstream>
#include <iostream>

/**
 * @file g_benchmark.cpp
 * @brief Benchmark de la fonction Mapper::analyzeRead() avec un vrai génome de référence (E. coli).
 */

std::string genome_path = "./e_coli_genome.fasta";  // Par défaut

/**
 * @brief Lit la séquence génomique depuis un fichier FASTA (première séquence uniquement).
 * @param filepath Chemin du fichier FASTA
 * @return La séquence concaténée du génome
 */
std::string loadGenomeFromFasta(const std::string& filepath) {
    ReadFasta reader(filepath);         // Création d'un lecteur FASTA
    reader.load();                      // Chargement des séquences
    const auto& sequences = reader.getSequences();
    if (!sequences.empty()) {
        return sequences[0].getSequence();  // Retourne la première séquence trouvée
    }
    return "";  // Si aucun read valide, retourne une chaîne vide
}

/**
 * @brief Benchmark de Mapper::analyzeRead() en utilisant le génome passé en argv
 *        et un petit ensemble de reads simulés issus du génome.
 */
static void BM_MapReads(benchmark::State& state) {
    std::string genome = loadGenomeFromFasta(genome_path);

    // Simulation de quelques reads à partir de la séquence du génome (reads parfaits)

    std::vector<Sequence> reads = {
        Sequence("read1", genome.substr(1000, 50)),
        Sequence("read2", genome.substr(2000, 50)),
        Sequence("read3", genome.substr(3000, 50))
    };

    // Boucle de benchmark (répétée automatiquement par Google Benchmark)
    for (auto _ : state) {
        Mapper mapper(15);  // Création d'un Mapper avec k = 15
        mapper.getGenomeIndex().indexGenome(genome);  // Indexation du génome

        // Analyse de chaque read sur le génome indexé
        for (const auto& read : reads) {
            benchmark::DoNotOptimize(mapper.analyzeRead(read));  // Empêche l'optimisation du compilateur
        }

        benchmark::ClobberMemory();  // Force la prise en compte mémoire par le benchmark
    }
}
BENCHMARK(BM_MapReads)
    ->Iterations(5) //5 itérations pour affiner le résultat
    ->Unit(benchmark::kMillisecond); //result plus lisible

/**
 * @brief Benchmark de KmerIndex::indexGenome() sur le génome E. coli
 *        Permet d'évaluer la rapidité de l'indexation des k-mers.
 */
static void BM_IndexGenome(benchmark::State& state) {
    std::string genome = loadGenomeFromFasta(genome_path);

    for (auto _ : state) {
        KmerIndex index(15);  // k = 15
        index.indexGenome(genome);  // Indexation du génome
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_IndexGenome)
    ->Iterations(5) //5 itérations pour affiner le résultat
    ->Unit(benchmark::kMillisecond); //result plus lisible

/**
 * @brief Benchmark de KmerIndex::searchKmerWithStrand() sur un génome indexé.
 *        On teste la recherche d'un k-mer fréquent pour mesurer la latence.
 */
static void BM_SearchKmerWithStrand(benchmark::State& state) {
    std::string genome = loadGenomeFromFasta(genome_path);
    KmerIndex index(15);
    index.indexGenome(genome);
    std::string strand;
    std::string kmer = genome.substr(1000, 15);  // Un k-mer connu

    for (auto _ : state) {
        benchmark::DoNotOptimize(index.searchKmerWithStrand(kmer, strand));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_SearchKmerWithStrand)
    ->Iterations(5)
    ->Unit(benchmark::kMicrosecond);

// === MAIN MODIFIÉ POUR PRENDRE UN FICHIER EN ARGUMENT ===
int main(int argc, char** argv) {
    if (argc > 1) {
        genome_path = argv[1];
        std::cout << "Utilisation du fichier génome : " << genome_path << std::endl;
    } else {
        std::cerr << "[Info] Aucun fichier FASTA passé. Utilisation du génome par défaut : " << genome_path << std::endl;
    }

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
    benchmark::Shutdown();
    return 0;
}
