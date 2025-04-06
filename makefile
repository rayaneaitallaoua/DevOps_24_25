# Makefile principal pour compiler un projet C++ avec C++17
# -------------------------------------
# Ce fichier remplace CMake pour la compilation manuelle

# === Variables ===
CXX = g++
CXXFLAGS = -std=c++17 -O2 -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lbenchmark -lpthread
SRC_DIR = src

# === Fichiers spécifiques ===
MAIN_SRC = $(SRC_DIR)/main.cpp
BENCH_SRC = $(SRC_DIR)/g_benchmark.cpp
OTHER_SRCS = $(filter-out $(MAIN_SRC) $(BENCH_SRC), $(wildcard $(SRC_DIR)/*.cpp))

# === Exécutables ===
MAIN_EXEC = my_program
BENCH_EXEC = g_benchmark

# === Cible par défaut ===
all: $(MAIN_EXEC) $(BENCH_EXEC)

# === Compilation du programme principal ===
$(MAIN_EXEC): $(MAIN_SRC) $(OTHER_SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# === Compilation du benchmark Google Benchmark ===
$(BENCH_EXEC): $(BENCH_SRC) $(OTHER_SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# === Nettoyage ===
clean:
	rm -f $(MAIN_EXEC) $(BENCH_EXEC) $(SRC_DIR)/*.o mapping_results.csv

.PHONY: all clean