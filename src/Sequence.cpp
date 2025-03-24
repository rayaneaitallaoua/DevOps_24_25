/**
* @file Sequence.cpp
 * @brief Implémentation de la classe Sequence
 */

#include "Sequence.hpp"
#include <iostream>

/**
 * @brief Constructeur pour une séquence sans qualité (ex : FASTA).
 * @param id Identifiant de la séquence
 * @param sequence La chaîne de caractères représentant la séquence (ACGT...)
 */
Sequence::Sequence(const std::string& id, const std::string& sequence)
    : id(id), sequence(sequence), quality("") {}

/**
 * @brief Constructeur pour une séquence avec qualité (ex : FASTQ).
 * @param id Identifiant de la séquence
 * @param sequence Séquence de base (ACGT...)
 * @param quality Chaîne de qualité (même longueur que sequence)
 */
Sequence::Sequence(const std::string& id, const std::string& sequence, const std::string& quality)
    : id(id), sequence(sequence), quality(quality) {}

/**
 * @brief Affiche la séquence dans le format FASTA ou FASTQ
 */
void Sequence::print() const {
    if (quality.empty()) {
        std::cout << ">" << id << "\n" << sequence << std::endl;
    } else {
        std::cout << "@" << id << "\n" << sequence << "\n+\n" << quality << std::endl;
    }
}

/**
 * @brief Retourne l'identifiant de la séquence
 * @return L'ID
 */
std::string Sequence::getId() const {
    return id;
}

/**
 * @brief Retourne la séquence de base (ACGT...)
 * @return La séquence
 */
std::string Sequence::getSequence() const {
    return sequence;
}

/**
 * @brief Retourne la chaîne de qualité (si disponible)
 * @return La chaîne de qualité, ou vide si FASTA
 */
std::string Sequence::getQuality() const {
    return quality;
}
