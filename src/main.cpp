#include "Mapper.hpp"
#include <iostream>
#include <filesystem>

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <reference.fasta> <reads_directory> <k> <min_hits>\n";
        return 1;
    }

    std::string refPath = argv[1];
    std::string readsDir = argv[2];
    int k = std::stoi(argv[3]);

    Mapper mapper(k);

    std::cout << "Loading reference genome...\n";
    mapper.loadReference(refPath);

    std::cout << "Loading reads from directory...\n";
    mapper.loadReadsFromDirectory(readsDir);
    std::cout << "Nombre de reads chargés : " << mapper.getReads().size() << "\n";

    std::cout << "Mapping reads...\n";
    mapper.mapReads();

    std::string outputDir;
    std::cout << "Veuillez entrer le dossier où enregistrer les résultats : ";
    std::getline(std::cin, outputDir);

    // Vérifie si le dossier existe
    if (!std::filesystem::exists(outputDir)) {
        std::cerr << "Erreur : le dossier n'existe pas.\n";
        return 1;
    }

    // Construit le chemin final du fichier CSV
    std::string outputPath = outputDir;
    if (outputPath.back() != '/' && outputPath.back() != '\\')
        outputPath += "/";
    outputPath += "mapping_results.csv";

    mapper.exportMappingsToCSV(outputPath);
    std::cout << "Résultats exportés dans : " << outputPath << "\n";

    return 0;
}