# push_swap

## Sujet :

Le but de ce projet est de trier en moins de coup possible une liste de nombre. Pour cela, on a droit d'utiliser 2 listes
et les instructions suivantes :
* sa : Echange les premier et second éléments de la liste A
* sb : Echange les premier et second éléments de la liste B
* ss : Echange les premier et second éléments des listes A et B (indépendamment l'une de l'autre)
* ra : "Tourne" la liste A au sens horaire en envoyant son premier élément à la fin.
* rb : "Tourne" la liste B au sens horaire en envoyant son premier élément à la fin.
* rr : "Tourne" les deuxlistes au sens horaire en envoyant leur premier élément à la fin.
* rra : "Tourne" la liste A au sens anti-horaire en envoyant son premier élément à la fin.
* rrb : "Tourne" la liste B au sens anti-horaire en envoyant son premier élément à la fin.
* rrr : "Tourne" les deuxlistes au sens anti-horaire en envoyant leur premier élément à la fin.
* pa : Envoit le premier élément de B au début de A
* pb : Envoit le premier élément de A au début de B

Nous devions aussi créer un petit programme "Checker" qui vérifie que la liste d'instructions fournit par push_swap trie effectivement la liste de nombre spécifiée.

## Mon implémentation :

L'idée générale est de diviser la liste en paquet de nombre croissants (mais non ordonnés) dans B pour les trier puis de les renvoyer à la fin de A. 

Voici les étapes que mon algorithme suit :
1. Envoyer la moitié inférieur dans B (en tournant A)
2. Renvoyer la moitié supérieur de B dans A (en tournant B)
3. Faire cela en boucle tant que le nombre d'éléments dans B est supérieur à 9 
4. Trier le paquet dans B, le renvoyer dans A, et tourner A pour qu'il soit à la fin
5. Renvoyer le prochain paquer de A au début de B
6. S'il a plus de 9 élément, reprendre depuis l'étape 2, sinon depuis l'étape 4
7. Faire cela en boucle tant que la lsite n'est pas entièrement triée.
[IMAGE A RAJOUTER]

On se retrouve à la fin avec A contenant des paquest triés de N (< 9) élément par odre croissant.
Tout au long de ce processus, il y a quelques améliorations permettant d'être plus efficace. Par exemple, quand je tourne dans B pour le trier ou renvoyer une partie de ces éléments, si je tombe sur le prochain nombre dont A à besoin, je le lui envoie directement.

Mon programme fait encore des mouvements inutile par moment, pour parer à cela, j'aurais pu parcourir la liste de toutes mes instructions et remplacer les redondances ou les actions s'annulant.

Prenons en exemple une liste avec les nombres de 0 à 100. Le symbole "!" signifie "trié" et le symbole "#" non-trié.
J'ai sauté les étapes répétives.

A : [0 - 99 #]  
B :
-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - 
A : [50 - 99 #]  
B : [0 - 49 #]
-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - 
A : [25 - 49 #] [50 - 100 #]  
B : [0 - 24 #]
-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - 
A : [6 - 11 #] [12 - 24 #] [25 - 49 #] [50 - 100 #]  
B : [0 - 5 #]
-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - 
A : [6 - 11 #] [12 - 24 #] [25 - 49 #] [50 - 100 #]  
B : [0 - 5 !]
-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - 
A : [0 - 5 !] [6 - 11 #] [12 - 24 #] [25 - 49 #] [50 - 100 #]  
B : 
-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - 
A : [6 - 11 #] [12 - 24 #] [25 - 49 #] [50 - 100 #][0 - 5 !]  
B : 
-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - 
A : [0 - 5 !] [6 - 11 !] [12 - 18 !] [19 - 24 !] [25 - 37 !] [38 - 49 !] [50 - 56 !]
 [57 - 62 !] [63 - 69 !] [70 - 75 !] [76 - 82 !] [83 - 87 !] [88 - 94 !] [95 - 99 !]  
B :  

[SIMPLIFIER EN PRENANT UNE LISTE DE 50]

## Visualisation :
J'ai fait une visualisation simple montrant le contenu des deux listes (avec une ellipse si elles sont trop grandes) et le dernier mouvement en couleur.
[IMAGE A RAJOUTER]
