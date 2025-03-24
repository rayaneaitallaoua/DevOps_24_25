#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>

// Liste les fichiers d'un dossier donné
std::vector<std::string> listFilesInDirectory(const std::string& dirPath);

// Détecte si un fichier est FASTA ou FASTQ
std::string detectFileFormat(const std::string& filename);

#endif