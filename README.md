# Optical fibre network reconstruction in C

English · [Français](README.fr.md)

A university project about representing and reconstructing networks from chains of points. It compares linked-list, hash-table and quadtree approaches, and contains graph routines for paths and capacity constraints.

## Structure

| Component | Purpose |
| --- | --- |
| [Chaine.c](Chaine.c) | Read chains of points from `.cha` datasets. |
| [Reseau.c](Reseau.c) | Build a network of nodes, neighbours and endpoint pairs. |
| [Hachage.c](Hachage.c) | Reconstruct a network using a hash table. |
| [ArbreQuat.c](ArbreQuat.c) | Use a spatial quadtree to find or create nodes. |
| [Graphe.c](Graphe.c) | Graph construction, path routines and network reorganization logic. |
| [Struct_File.c](Struct_File.c), [Struct_Liste.c](Struct_Liste.c) | Queue and list helpers for graph operations. |
| [SVGwriter.c](SVGwriter.c) | Generate browser-viewable network drawings. |

The main algorithmic comparison concerns how an existing point is found when rebuilding the network: scanning a list, looking in a hash table or searching a spatial tree. The graph layer represents vertices, edges and endpoint pairs, with a capacity parameter `gamma`.

## Build

Use **GCC, GNU Make and a POSIX environment**, such as Linux or Debian under WSL. The Makefile links the math library. From the repository root:

```sh
make
```

This builds `main`, `ReseauMain` and `GrapheMain`.

## Run the checked reconstruction examples

`ReseauMain` uses the included `00014_burma.cha` dataset. Select the data structure with one argument:

```sh
./ReseauMain 1  # linked list
./ReseauMain 2  # hash table
./ReseauMain 3  # quadtree
```

Run from the repository root so the fixed dataset filename resolves. Each mode writes a network description and an HTML drawing:

| Mode | Outputs |
| --- | --- |
| 1 | `reseauListe.txt`, `reseauListe.html` |
| 2 | `reseauHachage.txt`, `reseauHachage.html` |
| 3 | `reseauArbre.txt`, `reseauArbre.html` |

Open the generated HTML file in a browser to inspect the drawing. These commands overwrite outputs of the same name, including the existing `reseauListe.txt` file.

## Other entry points and known limits

- `main` is a timing driver with three fixed dataset filenames. It writes `mesures.txt`; its benchmark was not run for this documentation, so no performance ranking is claimed.
- `GrapheMain` takes a dataset filename, but its graph demonstration is currently failing. Under Debian/WSL, `./GrapheMain 00014_burma.cha` aborted with a glibc memory-allocation assertion (exit code 134). Graph routines are present, but this path must not be treated as a working demo.
- The build emits a `control reaches end of non-void function` warning in `Hachage.c`.

## Verification

On **17 November 2026**, `make` completed and all three `ReseauMain` examples exited with code 0 under Debian/WSL, producing their output files. This is a bounded demonstration check, not an automated correctness or memory-safety test suite. The graph failure and compiler warning remain documented; this documentation change does not modify the C implementation.

The existing [license](LICENSE) applies.

[More projects by Illia](https://github.com/IBZua/project-showcase)
