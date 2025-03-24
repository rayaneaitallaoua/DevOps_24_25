/**
* @file Sequence.hpp
 * @brief Déclaration de la classe Sequence pour représenter un read (FASTA ou FASTQ).
 */

#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <string>
#include <iostream>

/**
 * @class Sequence
 * @brief Représente une séquence lue depuis un fichier FASTA ou FASTQ.
 */
class Sequence {
public:
    /**
     * @brief Constructeur pour une séquence sans qualité (ex : FASTA).
     * @param id Identifiant de la séquence
     * @param sequence La chaîne nucléotidique (ACGT...)
     */
    Sequence(const std::string& id, const std::string& sequence);

    /**
     * @brief Constructeur pour une séquence avec qualité (ex : FASTQ).
     * @param id Identifiant
     * @param sequence Séquence nucléotidique
     * @param quality Chaîne de qualité (ASCII)
     */
    Sequence(const std::string& id, const std::string& sequence, const std::string& quality);

    /**
     * @brief Affiche la séquence au format FASTA ou FASTQ.
     */
    void print() const;

    /**
     * @brief Retourne l'identifiant de la séquence.
     * @return L'ID
     */
    std::string getId() const;

    /**
     * @brief Retourne la séquence nucléotidique.
     * @return La séquence
     */
    std::string getSequence() const;

    /**
     * @brief Retourne la chaîne de qualité (s'il y en a une).
     * @return La qualité
     */
    std::string getQuality() const;

private:
    std::string id;       /**< Identifiant de la séquence */
    std::string sequence; /**< Nucléotides ACGT... */
    std::string quality;  /**< Qualité (FASTQ) ou vide (FASTA) */
};

#endif