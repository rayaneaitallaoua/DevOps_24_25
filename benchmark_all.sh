#!/bin/bash

# === Configuration ===
GENOME_DIR="./genomes"
BENCH_EXEC="./g_benchmark"
OUTPUT_FILE="result_benchmarking.txt"

# === Vider ou créer le fichier de sortie ===
echo "== Résultats du benchmarking ==" > "$OUTPUT_FILE"
echo "Date : $(date)" >> "$OUTPUT_FILE"
echo "" >> "$OUTPUT_FILE"

# === Boucle sur chaque fichier FASTA ===
for genome in "$GENOME_DIR"/*.fasta; do
  echo "Benchmarking: $genome"

  echo "=============================" >> "$OUTPUT_FILE"
  echo "Fichier : $genome" >> "$OUTPUT_FILE"
  echo "Taille : $(grep -v '^>' "$genome" | tr -d -c 'ACGTacgt' | wc -c) bp" >> "$OUTPUT_FILE"
  echo "-----------------------------" >> "$OUTPUT_FILE"

  # Exécution avec redirection standard sortie et erreur
  /usr/bin/time -l "$BENCH_EXEC" "$genome" >> "$OUTPUT_FILE" 2>&1

  echo "" >> "$OUTPUT_FILE"
done

echo "Résultats enregistrés dans $OUTPUT_FILE"