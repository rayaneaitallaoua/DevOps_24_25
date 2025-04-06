#ifndef BENCHMARK_SUITE_HPP
#define BENCHMARK_SUITE_HPP

#include <benchmark/benchmark.h>
#include "Utils.hpp"
#include "KmerIndex.hpp"
#include "Mapper.hpp"
#include "Sequence.hpp"
#include <vector>
#include <string>

/**
 * @file benchmark_suite.hpp
 * @brief Déclaration des fonctions de benchmark pour les composants clés du projet de mapping.
 */

/**
 * @brief Benchmark de la fonction reverseComplement de Utils.
 * Mesure le temps de calcul du brin complémentaire inversé d'une séquence.
 */
void BM_ReverseComplement(benchmark::State& state);

#endif // BENCHMARK_SUITE_HPP