/**
* @file ReadFasta.hpp
 * @brief Déclaration de la classe ReadFasta pour la lecture de fichiers FASTA.
 */

#ifndef READFASTA_HPP
#define READFASTA_HPP

#include <string>
#include <vector>
#include "Sequence.hpp"

/**
 * @class ReadFasta
 * @brief Classe permettant de lire un fichier FASTA et d'en extraire les séquences valides.
 */
class ReadFasta {
public:
    /**
     * @brief Constructeur
     * @param filename Le chemin du fichier FASTA à lire
     */
    ReadFasta(const std::string& filename);

    /**
     * @brief Charge les séquences à partir du fichier FASTA
     */
    void load();

    /**
     * @brief Affiche les séquences valides sur la sortie standard
     */
    void printSequences() const;

    /**
     * @brief Retourne les séquences valides lues depuis le fichier
     * @return Un vecteur de Sequence valides
     */
    std::vector<Sequence> getSequences() const;

private:
    std::string filename;             /**< Chemin vers le fichier FASTA */
    std::vector<Sequence> sequences; /**< Séquences valides extraites du fichier */
};

#endif
