/**
 * @file ReadFasta.cpp
 * @brief Implémentation de la classe ReadFasta pour la lecture de fichiers FASTA.
 */

#include "ReadFasta.hpp"
#include <fstream>
#include <iostream>

/**
 * @brief Constructeur de la classe ReadFasta
 * @param filename Le chemin vers le fichier FASTA à lire
 */
ReadFasta::ReadFasta(const std::string& filename) : filename(filename) {}

/**
 * @brief Charge les séquences valides à partir du fichier FASTA.
 *
 * Les séquences malformées sont ignorées avec un message d'erreur :
 * - Si une ligne de séquence précède un header '>'
 * - Si une séquence contient des caractères autres que A, C, G ou T
 */
void ReadFasta::load() {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    std::string line, seq_id, sequence;
    bool valid = true;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        if (line[0] == '>') {
            if (!seq_id.empty()) {
                if (valid) {
                    sequences.emplace_back(seq_id, sequence);
                } else {
                    std::cerr << "Warning: Non-ACGT character detected in sequence " << seq_id << ". Sequence was ignored." << std::endl;
                }
            }
            seq_id = line.substr(1);
            sequence.clear();
            valid = true;
        } else {
            if (seq_id.empty()) {
                std::cerr << "Error: Malformed FASTA file. Missing '>' before sequence. Sequence ignored." << std::endl;
                continue;
            }
            for (char c : line) {
                if (c != 'A' && c != 'C' && c != 'G' && c != 'T') {
                    valid = false;
                }
            }
            sequence += line;
        }
    }

    if (!seq_id.empty()) {
        if (valid) {
            sequences.emplace_back(seq_id, sequence);
        } else {
            std::cerr << "Warning: Non-ACGT character detected in sequence " << seq_id << ". Sequence was ignored." << std::endl;
        }
    }
}

/**
 * @brief Affiche les séquences valides extraites du fichier
 */
void ReadFasta::printSequences() const {
    for (const auto& seq : sequences) {
        seq.print();
    }
}

/**
 * @brief Retourne les séquences valides lues depuis le fichier
 * @return Un vecteur contenant les objets Sequence valides
 */
std::vector<Sequence> ReadFasta::getSequences() const {
    return sequences;
}
