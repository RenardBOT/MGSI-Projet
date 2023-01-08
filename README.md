# MGSI-Projet
Projet de MGSI (Modélisation Géométrique et Synthèse d'Images)

## Execution
Pour executer l'application, il faut se situer à la racine du projet, FORCEMENT. Depuis la racine, il faut lancer l'executable dans le dossier bin. Voici la commande 

```bash
~/<chemin>/MGSI-Projet$  bin/mgsi <arguments>
```

Se déplacer dans bin, et y executer mgsi ne marchera PAS.\
**A ne pas faire :**
```bash
~/<chemin>/MGSI-Projet$  cd bin/
~/<chemin>/MGSI-Projet/bin$  ./mgsi
```

## Arguments

Il est possible (et nécessaire) d'inclure des arguments lors de l'execution :

- **NECESSAIRE** `-a <int> :` Sommet de départ de la trajectoire (ligne du fichier obj)
- **NECESSAIRE** `-b <int> :` Sommet d'arrivée de la trajectoire (ligne du fichier obj)
- **NECESSAIRE** `-p "nom-fichier" :` Nom du fichier obj SANS L'EXTENSION, dans le dossier meshes (par exemple `"ours"` ou `"sphere"`)
- **NECESSAIRE** `-d <0|1> :` Choix de l'algorithme (0 pour dijkstra non pondéré, 1 pour dijkstra pondéré)
- **OPTIONNEL** `-z <float> :` Valeur du zoom (par défaut 1.0)

## Entrées clavier

Il est possible de manipuler la scène à l'appui de touches du clavier :

### Rendu

- `w :` Activer/Desactiver le mode fil de fer
- `f :` Activer/Desactiver le mode faces pleines
- `p :` Activer/Desactiver l'affichage de la trajectoire

### Rotations (ZQSD)

- `z :` Rotation de la caméra vers l'avant
- `s :` Rotation de la caméra vers l'arrière
- `a :` Rotation de la caméra vers la gauche
- `e :` Rotation de la caméra vers la droite
- `a :` Rotation de la caméra vers la gauche centrée sur l'origine
- `e :` Rotation de la caméra vers la droite centrée sur l'origine

### Translation (IJKL)

- `i :` Translation de la caméra vers l'avant
- `k :` Translation de la caméra vers l'arrière
- `j :` Translation de la caméra vers la gauche
- `l :` Translation de la caméra vers la droite
- `u :` Translation de la caméra vers le bas
- `o :` Translation de la caméra vers le haut

## Installation des librairies
Plusieurs librairies sont nécéssaires pour le faire fonctionner le projet :\
**SDL 1.2, GLM et GLEW**\
Version de **GLSL : 4.30** (shaders compatibles 4.60 entre autres)
Pour les installer : 
```bash
sudo apt-get install libsdl1.2-dev libglm-dev libglew-dev    
```

## Compilation

Utiliser le makefile à la racine du projet pour compiler.

Pour **compiler tout le projet**
```bash
make
```

Pour **nettoyer les fichiers objets et l'executable**
```bash
make clean
```

Pour **effectuer les deux à la fois**, ce qui peut être utile pour vérifier s'il y a des Warnings à la compilation
```bash
make remake
```


## Répertoires
* bin : Contient l'executable
* meshes : contient les fichiers .obj et .mtl pour afficher des objets
* obj : Contient les fichiers objets et dépendances (.o et .d) à la compilation. Le contenu de ce dossier fait partie du gitignore.
* shaders : Contient les shaders vertex et fragment
* src : Code source .cpp et headers .hpp
