#include <benchmark/benchmark.h>
#include "Utils.hpp"
#include <vector>
#include <string>
#include <fstream>

// ======================= reverseComplement =======================
static void BM_ReverseComplement(benchmark::State& state) {
    std::string seq = "AGCTTAGCTAAGCTTAGCTAAGCTTAGCTAAGCTTAGCTA";
    for (auto _ : state) {
        benchmark::DoNotOptimize(reverseComplement(seq));
    }
}
BENCHMARK(BM_ReverseComplement);