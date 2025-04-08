# Projet de Développement Opérationnel Avancé 2025

**Auteur** : Rayane Ayoub AIT ALLAOUA.

**Contexte** : Projet universitaire réalisé dans le cadre de l’UE HAU803I — Master Bioinformatique  
**Sujet** : Développement d’un outil de mapping de reads génomiques sur un génome de référence

---

## Objectifs du projet

Ce projet a pour but d’implémenter un outil permettant :

- La lecture de fichiers au format FASTA et FASTQ
- Le nettoyage et la validation des séquences lues
- L’indexation d’un génome en k-mers
- Le mapping des reads sur le génome de référence, avec gestion du brin complémentaire
- L’affichage ou l’export des résultats d’alignement

---

## Compilation

Le projet peut être compilé avec n’importe quel compilateur compatible C++17.

```bash
g++ -std=c++17 -o main main.cpp *.cpp
```

Un fichier `Makefile` est également fourni pour automatiser la compilation :

```bash
make
```

---

## Utilisation

Le programme s’utilise en ligne de commande :

```bash
./main <genome.fasta> <dossier_reads> <taille_kmer>
```

- `<genome.fasta>` : le génome de référence en format FASTA.
- `<dossier_reads>` : chemin vers le dossier contenant les fichiers des reads
- `<taille_kmer>` : taille des k-mers utilisés pour l’indexation

---

## Principaux composants du projet

| Composant        | Description                                                               |
|------------------|---------------------------------------------------------------------------|
| `Sequence`       | Classe de base représentant une séquence biologique                       |
| `ReadFasta`, `ReadFastq` | Lecture, validation et nettoyage des fichiers d’entrée                    |
| `KmerIndex`      | Indexation du génome par k-mers                                           |
| `Mapper`         | Algorithme de mapping basé sur un système de vote                         |
| `Utils`          | Fonctions utilitaires (nettoyage, brin complément inverse, parsing, etc.) |

---

## Documentation

La documentation est générée automatiquement avec Doxygen.

Pour la générer :

```bash
doxygen
```

La documentation HTML sera disponible dans le dossier `./doc/html/index.html`.
---

## Licence

Ce projet est distribué sous la **licence CeCILL**, une licence libre conforme au droit français et compatible avec la GNU GPL.
Le texte complet de la licence est disponible à l'adresse suivante :  
<https://cecill.info/licences/Licence_CeCILL_V2.1-fr.html>