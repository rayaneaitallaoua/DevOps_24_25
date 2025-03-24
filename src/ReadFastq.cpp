/**
 * @file ReadFastq.cpp
 * @brief Implémentation de la classe ReadFastq pour la lecture de fichiers FASTQ.
 */

#include "ReadFastq.hpp"
#include <fstream>
#include <iostream>

/**
 * @brief Constructeur de ReadFastq.
 * @param filename Le chemin vers le fichier FASTQ à traiter.
 */
ReadFastq::ReadFastq(const std::string& filename) : filename(filename) {}

/**
 * @brief Charge les reads valides à partir du fichier FASTQ.
 *
 * Chaque read FASTQ est composé de 4 lignes :
 * - Ligne 1 : identifiant précédé de '@'
 * - Ligne 2 : séquence nucléotidique
 * - Ligne 3 : ligne '+' (séparateur)
 * - Ligne 4 : chaîne de qualité (même longueur que la séquence)
 *
 * Si l'un de ces éléments est absent ou mal formé, le read est ignoré avec un message d'erreur.
 */
void ReadFastq::load() {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    std::string id, sequence, plus_line, quality;

    while (std::getline(file, id)) {
        if (id.empty()) continue;

        if (id[0] != '@') {
            std::cerr << "Error: Malformed FASTQ entry. Expected '@'. Sequence ignored." << std::endl;
            continue;
        }

        if (!std::getline(file, sequence) || sequence.empty()) {
            std::cerr << "Error: Missing sequence for " << id << ". Sequence ignored." << std::endl;
            continue;
        }

        if (!std::getline(file, plus_line) || plus_line[0] != '+') {
            std::cerr << "Error: Missing '+' separator for " << id << ". Sequence ignored." << std::endl;
            continue;
        }

        if (!std::getline(file, quality) || quality.empty()) {
            std::cerr << "Error: Missing quality string for " << id << ". Sequence ignored." << std::endl;
            continue;
        }

        if (sequence.length() != quality.length()) {
            std::cerr << "Error: Quality length does not match sequence length for " << id << ". Sequence ignored." << std::endl;
            continue;
        }

        // Retire le '@' de l'identifiant et ajoute la sequence valide
        reads.emplace_back(id.substr(1), sequence, quality);
    }
}

/**
 * @brief Affiche les reads valides au format FASTQ sur la sortie standard.
 */
void ReadFastq::printReads() const {
    for (const auto& read : reads) {
        read.print();
    }
}

/**
 * @brief Retourne la liste des reads valides extraits du fichier.
 * @return Un vecteur d'objets Sequence correspondant aux reads valides.
 */
std::vector<Sequence> ReadFastq::getReads() const {
    return reads;
}
