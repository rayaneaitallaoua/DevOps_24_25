Ce fichier décrit le porjet dans ses grands lignes. et explique les différentes étapes à réaliser pour son installation

# Demo
démo du prof pour UE HAU803I (DevOps)

les commandes basiques de git : 
`git status`
`git log`
`git add`
`git rm`
`git diff`

Reminder: fix the names .H to .hpp mess in ReadFasta/q and sequence

Mon gameplan:

Semaine 1 : Développement de l’algorithme et de la structure de données
1.	Jours 1-2 : Comprendre les fichiers FASTA/FASTQ
•	Lire et comprendre la structure de ces fichiers.
•	Écrire un code simple en C++ pour lire un fichier FASTA/FASTQ.
2.	Jours 3-4 : Définir la structure de données pour l’indexation des k-mers
•	Implémenter une table de hachage ou un suffix array pour stocker les positions des k-mers.
•	Tester avec un petit génome et quelques reads.
3.	Jours 5-6 : Implémenter l’algorithme de mapping
•	Parcourir les reads, extraire les k-mers et les comparer avec la structure indexée.
•	Prendre en compte les mutations et erreurs de séquençage.
•	Générer un fichier de sortie avec les positions des reads.
4.	Jour 7 : Débogage et tests initiaux
•	Vérifier les performances sur un petit dataset.

⸻

Semaine 2 : Optimisation, comparaison et rédaction
5.	Jours 8-9 : Comparaison avec des outils existants (BWA, Bowtie, etc.)
•	Lancer ton algorithme et comparer les résultats avec ceux d’outils connus.
•	Noter les différences en termes de précision et de vitesse.
6.	Jours 10-11 : Optimisation du code
•	Améliorer la gestion de la mémoire et l’efficacité de la recherche.
•	Vérifier la complexité spatiale et temporelle.
7.	Jour 12 : Rédaction du rapport
•	Expliquer tes choix d’algorithmes et de structures de données.
•	Décrire les résultats obtenus et comparer avec les autres outils.
8.	Jour 13 : Finalisation et préparation de la soutenance
•	Préparer une présentation claire.
•	Tester tes explications à l’oral.
9.	Jour 14 : Vérifications finales
•	Corriger d’éventuelles erreurs et améliorer la clarté du code.

To Do:

handle degenarted DNA alphabet: R N ...
