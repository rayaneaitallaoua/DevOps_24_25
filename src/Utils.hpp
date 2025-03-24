/**
* @file Utils.hpp
 * @brief Fonctions utilitaires pour la gestion des fichiers et des séquences ADN.
 */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

/**
 * @brief Liste tous les fichiers d'un dossier donné.
 * @param dirPath Chemin vers le dossier à explorer
 * @return Un vecteur contenant les chemins de chaque fichier trouvé
 */
std::vector<std::string> listFilesInDirectory(const std::string& dirPath);

/**
 * @brief Détecte le format FASTA ou FASTQ d'un fichier en analysant sa première ligne.
 * @param filename Chemin vers le fichier à analyser
 * @return "fasta", "fastq" ou "unknown"
 */
std::string detectFileFormat(const std::string& filename);

/**
 * @brief Calcule le brin complémentaire inversé d'une séquence ADN.
 * @param seq La séquence d'origine (A, C, G, T)
 * @return Le brin complémentaire inversé de la séquence
 */
std::string reverseComplement(const std::string& seq);

#endif
