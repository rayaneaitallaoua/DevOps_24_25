#include "Mapper.hpp"
#include <iostream>
#include <cstdlib> // Pour std::stoi

int main(int argc, char* argv[]) {
    // Vérifie si les bons arguments sont fournis
    if (argc < 5) {
        std::cerr << "Usage: " << argv[0] << " <reference.fasta> <reads_directory> <k> <min_hits>\n";
        return 1;
    }

    std::string ref_file = argv[1];     // Fichier FASTA du génome de référence
    std::string reads_dir = argv[2];    // Dossier contenant les reads
    int k = std::stoi(argv[3]);         // Longueur des k-mers (convertie de string à int)
    int min_hits = std::stoi(argv[4]);  // Seuil minimum de hits pour considérer un mapping valide

    // Instancie la classe Mapper avec les valeurs définies par l'utilisateur
    Mapper mapper(k, min_hits);

    std::cout << "Loading reference genome...\n";
    mapper.loadReference(ref_file);

    std::cout << "Loading reads from directory...\n";
    mapper.loadReadsFromDirectory(reads_dir);

    std::cout << "Mapping reads...\n";
    mapper.mapReads();

    std::cout << "Mapping results:\n";
    mapper.printMappings();

    return 0;
}