# Makefile principal pour compiler un projet C++ avec C++17
# -------------------------------------
# Ce fichier remplace CMake pour la compilation manuelle

# Nom de l'exécutable final
TARGET = my_program

# Dossier des sources
SRC_DIR = src

# Dossier des entêtes
INC_DIR = include

# Liste automatique des fichiers source (.cpp)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Remplace chaque fichier .cpp par un .o dans le dossier courant
OBJS = $(SRCS:.cpp=.o)

# Compilateur et options
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I$(INC_DIR)

# Règle principale
all: $(TARGET)

# Lier les objets pour créer l'exécutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compiler chaque fichier source en objet
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

.PHONY: all clean