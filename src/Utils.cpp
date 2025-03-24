#include "Utils.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

// Fonction pour lister tous les fichiers d'un dossier
std::vector<std::string> listFilesInDirectory(const std::string& dirPath) {
    std::vector<std::string> files;
    try {
        for (const auto& entry : fs::directory_iterator(dirPath)) {
            if (fs::is_regular_file(entry.path())) {
                files.push_back(entry.path().string());
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: Unable to read directory " << dirPath << ": " << e.what() << std::endl;
    }
    return files;
}

// Fonction pour détecter si un fichier est FASTA ou FASTQ
std::string detectFileFormat(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return "unknown";
    }

    std::string firstLine;
    std::getline(file, firstLine);
    
    if (!firstLine.empty()) {
        if (firstLine[0] == '>') return "fasta";
        if (firstLine[0] == '@') return "fastq";
    }
    return "unknown";
}