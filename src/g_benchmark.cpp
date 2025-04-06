#include <benchmark/benchmark.h>
#include "Mapper.hpp"
#include "ReadFasta.hpp"
#include <fstream>

/**
 * @file g_benchmark.cpp
 * @brief Benchmark de la fonction Mapper::analyzeRead() avec un vrai génome de référence (E. coli).
 */

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
 * @brief Benchmark de Mapper::analyzeRead() en utilisant un génome réel (E. coli)
 *        et un petit ensemble de reads simulés issus du génome.
 */
static void BM_MapReads(benchmark::State& state) {
    // Chargement du génome de référence depuis un fichier FASTA réel (E. coli)
    std::string genome = loadGenomeFromFasta("./e_coli_genome.fasta");

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
    std::string genome = loadGenomeFromFasta("./e_coli_genome.fasta");

    for (auto _ : state) {
        KmerIndex index(15);  // k = 15
        index.indexGenome(genome);  // Indexation du génome
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_IndexGenome)
    ->Iterations(5) //5 itérations pour affiner le résultat
    ->Unit(benchmark::kMillisecond); //result plus lisible

BENCHMARK_MAIN();