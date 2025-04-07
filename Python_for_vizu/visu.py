import matplotlib.pyplot as plt

# ----------------------------------------
# Script for visualizing genome benchmarking results:
# - Real execution time (log scale bar chart)
# - Peak memory usage (log scale bar chart)
# - Execution time of 3 functions vs genome size (log-log line chart)
# ----------------------------------------

# Genome labels with approximate sizes for display purposes
genomes = [
    "E. coli (4Mb)",
    "S. cerevisiae (12Mb)",
    "C. elegans (100Mb)",
    "D. melanogaster (142Mb)",
    "O. sativa(386Mb)",
    "D. rerio (1.6Gb)"
]

# Real execution time in seconds for each genome
real_times = [
    6.52,
    1.30,
    19.87,
    34.98,
    75.04,
    888.70
]

# Times (in seconds) for three core operations
map_reads = [1.865, 0.0304, 5.93, 10.52, 23.41, 220.1]  # Mapping reads
index_genome = [1.77, 0.0307, 5.61, 11.3, 20.53, 119.9]  # Indexing the genome
search_kmer = [8.0e-6, 7.0e-6, 14.0e-6, 10.0e-6, 11.0e-6, 65.0e-6]  # Average k-mer search time (converted to seconds)

# Genome sizes in base pairs (bp), used as x-axis for log-log plot
genome_sizes = [4.6e6, 12.1e6, 100.2e6, 142.6e6, 386.3e6, 1.674e9]

# Peak memory usage in megabytes (MB)
peak_memory = [
    427,
    26,
    1180,
    1951,
    3382,
    4095
]

# Color scheme for bar charts
colors = plt.cm.viridis([0.1, 0.25, 0.4, 0.55, 0.7, 0.85])

# ----------------------------
# Plot 1: Real execution time (log-scale bar chart)
# ----------------------------
plt.figure(figsize=(10, 6))
plt.bar(genomes, real_times, color=colors)

plt.title("Temps réel d'exécution par génome", fontsize=14)
plt.xlabel("Génome", fontsize=12)
plt.ylabel("Temps réel (secondes)", fontsize=12)
plt.xticks(rotation=45)
plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.yscale('log')  # Use logarithmic scale for better visual spacing

plt.tight_layout()
plt.savefig("temps_execution_log.png", dpi=300)
plt.show()

# ----------------------------
# Plot 2: Peak memory usage (log-scale bar chart)
# ----------------------------
plt.figure(figsize=(10, 6))
plt.bar(genomes, peak_memory, color=colors)

plt.title("Mémoire maximale utilisée par génome", fontsize=14)
plt.xlabel("Génome", fontsize=12)
plt.ylabel("Mémoire pic (Mo)", fontsize=12)
plt.xticks(rotation=45)
plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.yscale('log')  # Logarithmic scale for memory

plt.tight_layout()
plt.savefig("memoire_execution_log.png", dpi=300)
plt.show()

# ----------------------------
# Plot 3: Time per function vs genome size (log-log line plot)
# ----------------------------
plt.figure(figsize=(10, 6))

# Plot each function's execution time against genome size
plt.plot(genome_sizes, map_reads, marker='o', label="MapReads")
plt.plot(genome_sizes, index_genome, marker='s', label="IndexGenome")
plt.plot(genome_sizes, search_kmer, marker='^', label="SearchKmer")

plt.title("Comparaison des temps d'exécution en fonction de la taille du génome", fontsize=14)
plt.xlabel("Taille du génome (bp)", fontsize=12)
plt.ylabel("Temps (secondes)", fontsize=12)
plt.xscale('log')  # Logarithmic x-axis for genome size
plt.yscale('log')  # Logarithmic y-axis for execution time
plt.grid(True, which="both", linestyle='--', alpha=0.7)
plt.legend()

plt.tight_layout()
plt.savefig("comparaison_temps_loglog.png", dpi=300)
plt.show()
