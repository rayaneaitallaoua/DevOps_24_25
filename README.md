# Advanced Operational Development Project 2025

**Author**: Rayane Ayoub AIT ALLAOUA.

**Context**: University project carried out as part of the HAU803I course — Bioinformatics Masters of the university of Montpellier
**Subject**: Development of a read mapping tool on a reference genome

---

## Project Objectives

The goal of this project is to implement a tool that allows:

- Reading files in FASTA and FASTQ formats
- Cleaning and validating the read sequences
- Indexing a genome using k-mers
- Mapping reads to the reference genome, including reverse complement strand support
- Displaying or exporting alignment results

---

## Compilation

The project can be compiled with any C++17 compatible compiler.

```bash
g++ -std=c++17 -o main main.cpp *.cpp
```

A `Makefile` is also provided to automate the compilation:

```bash
make
```

---

## Usage

The program is used via the command line:

```bash
./main <genome.fasta> <reads_folder> <kmer_size>
```

- `<genome.fasta>`: the reference genome in FASTA format.
- `<reads_folder>`: path to the folder containing the reads files
- `<kmer_size>`: size of the k-mers used for indexing

---

## Main Components of the Project

| Component         | Description                                                              |
|------------------|--------------------------------------------------------------------------|
| `Sequence`        | Base class representing a biological sequence                            |
| `ReadFasta`, `ReadFastq` | Reading, validation, and cleaning of input files                        |
| `KmerIndex`       | Genome indexing using k-mers                                              |
| `Mapper`          | Mapping algorithm based on a voting system                                |
| `Utils`           | Utility functions (cleaning, reverse complement, parsing, etc.)           |

---

## Documentation

The documentation is automatically generated with Doxygen.

To generate it:

```bash
doxygen
```

The HTML documentation will be available in the `./doc/html/index.html` folder.

---

## License

This project is distributed under the **CeCILL license**, a free software license compliant with French law and compatible with the GNU GPL.

The full license text is available at the following address:  
<https://cecill.info/licences/Licence_CeCILL_V2.1-en.html>