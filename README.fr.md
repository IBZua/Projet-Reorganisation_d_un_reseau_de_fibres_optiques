# Reconstruction d'un réseau de fibres optiques en C

[English](README.md) · Français

Un projet universitaire sur la représentation et la reconstruction de réseaux à partir de chaînes de points. Il compare des approches par listes chaînées, tables de hachage et arbres quaternaires, et contient des routines de graphes pour les chemins et contraintes de capacité.

## Organisation

| Composant | Rôle |
| --- | --- |
| [Chaine.c](Chaine.c) | Lire les chaînes de points des fichiers `.cha`. |
| [Reseau.c](Reseau.c) | Construire un réseau de nœuds, voisins et paires d'extrémités. |
| [Hachage.c](Hachage.c) | Reconstruire le réseau avec une table de hachage. |
| [ArbreQuat.c](ArbreQuat.c) | Chercher ou créer les nœuds dans un arbre quaternaire spatial. |
| [Graphe.c](Graphe.c) | Construire les graphes, chercher des chemins et réorganiser le réseau. |
| [Struct_File.c](Struct_File.c), [Struct_Liste.c](Struct_Liste.c) | Files et listes auxiliaires pour les graphes. |
| [SVGwriter.c](SVGwriter.c) | Produire des dessins consultables dans un navigateur. |

La comparaison algorithmique porte sur la recherche d'un point existant pendant la reconstruction : parcours d'une liste, recherche dans une table de hachage ou recherche spatiale dans un arbre. La couche graphe représente sommets, arêtes et paires d'extrémités, avec un paramètre de capacité `gamma`.

## Compiler

Utiliser **GCC, GNU Make et un environnement POSIX**, par exemple Linux ou Debian sous WSL. Le Makefile lie la bibliothèque mathématique. Depuis la racine du dépôt :

```sh
make
```

La commande produit `main`, `ReseauMain` et `GrapheMain`.

## Exécuter les exemples de reconstruction vérifiés

`ReseauMain` utilise le fichier fourni `00014_burma.cha`. Son argument choisit la structure de données :

```sh
./ReseauMain 1  # liste chaînée
./ReseauMain 2  # table de hachage
./ReseauMain 3  # arbre quaternaire
```

Exécuter depuis la racine du dépôt pour retrouver le fichier de données dont le nom est fixé dans le code. Chaque mode écrit une description du réseau et un dessin HTML :

| Mode | Fichiers produits |
| --- | --- |
| 1 | `reseauListe.txt`, `reseauListe.html` |
| 2 | `reseauHachage.txt`, `reseauHachage.html` |
| 3 | `reseauArbre.txt`, `reseauArbre.html` |

Ouvrir le fichier HTML généré dans un navigateur pour examiner le dessin. Ces commandes remplacent les sorties du même nom, dont le fichier existant `reseauListe.txt`.

## Autres points d'entrée et limites connues

- `main` mesure les temps sur trois fichiers de données aux noms fixes. Il écrit `mesures.txt` ; ce benchmark n'a pas été exécuté pour cette documentation et aucun classement de performances n'est revendiqué.
- `GrapheMain` prend un nom de fichier, mais sa démonstration de graphe échoue actuellement. Sous Debian/WSL, `./GrapheMain 00014_burma.cha` s'est interrompu sur une assertion d'allocation mémoire de glibc, avec le code de sortie 134. Les routines existent, mais ce parcours ne doit pas être présenté comme une démonstration fonctionnelle.
- La compilation émet l'avertissement `control reaches end of non-void function` dans `Hachage.c`.

## Vérification

Le **17 novembre 2026**, `make` a réussi et les trois exemples `ReseauMain` se sont terminés avec un code de sortie 0 sous Debian/WSL, en produisant leurs fichiers de sortie. C'est une vérification délimitée des démonstrations, pas une suite automatisée de correction algorithmique ou de sûreté mémoire. L'échec du graphe et l'avertissement de compilation restent documentés ; cette modification documentaire ne change pas l'implémentation C.

La [licence existante](LICENSE) s'applique.

[Autres projets d'Illia](https://github.com/IBZua/project-showcase/blob/main/README.fr.md)
