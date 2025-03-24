/**
* @file ReadFastq.hpp
 * @brief Déclaration de la classe ReadFastq pour la lecture de fichiers FASTQ.
 */

#ifndef READFASTQ_HPP
#define READFASTQ_HPP

#include <string>
#include <vector>
#include "Sequence.hpp"

/**
 * @class ReadFastq
 * @brief Gère la lecture et la validation de fichiers FASTQ contenant des reads avec qualité.
 *
 * Cette classe extrait les lectures valides depuis un fichier FASTQ en vérifiant :
 * - la présence des lignes de header (@) et séparateur (+)
 * - que la longueur de la séquence correspond à la chaîne de qualité
 */
class ReadFastq {
public:
    /**
     * @brief Constructeur
     * @param filename Chemin du fichier FASTQ à traiter
     */
    ReadFastq(const std::string& filename);

    /**
     * @brief Charge les reads valides depuis le fichier
     */
    void load();

    /**
     * @brief Affiche les reads valides au format FASTQ
     */
    void printReads() const;

    /**
     * @brief Retourne les lectures valides sous forme de vecteur de Sequence
     */
    std::vector<Sequence> getReads() const;

private:
    std::string filename;             /**< Chemin du fichier FASTQ */
    std::vector<Sequence> reads;     /**< Liste des reads valides extraits */
};

#endif
