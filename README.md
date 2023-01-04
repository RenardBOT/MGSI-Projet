# MGSI-Projet
Projet de MGSI (Modélisation Géométrique et Synthèse d'Images)

## Execution
Pour executer l'application, il faut se situer à la racine du projet, FORCEMENT. Depuis la racine, il faut lancer l'executable dans le dossier bin. Voici la commande 

```bash
~/<chemin>/MGSI-Projet$  bin/mgsi
```

Se déplacer dans bin, et y executer mgsi ne marchera PAS.\
**A ne pas faire :**
```bash
~/<chemin>/MGSI-Projet$  cd bin/
~/<chemin>/MGSI-Projet/bin$  ./mgsi
```

## Installation des librairies
Plusieurs librairies sont nécéssaires pour le faire fonctionner le projet :\
**SDL 1.2, GLM et GLEW**\
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
