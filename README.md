# TP TI202 Langage C
## Messages secrets avec RSA
Le système RSA permet d’échanger des messages secrets de manière très sécurisée.

Il est basé sur le principe de clé publique / clé privée.

Supposons qu’**Alice** veuille échanger des messages avec **Bob** :

>Elle doit fournir une **clé publique** à Bob
>
>Bob s’en servira pour **chiffrer** un message pour Alice
>
>Pour **déchiffrer** ce message, Alice utilisera sa **clé privée** (qu’elle n’a pas communiqué). Ainsi, elle est la seule à pouvoir déchiffrer le message de Bob
>
>Dans le sens inverse, Bob fournit une clé publique à Alice : Alice l’utilisera pour ‘chiffrer’ un message pour Bob. Bob utilisera sa clé privée (qu’Alice ne connaît pas) pour déchiffrer ce message.>

Pour cet exercice, nous utiliserons des nombres ‘pas trop grands’ pour les fonctions de calcul. 

Le type à utiliser pour les calculs  sera `uint64_t`  (format à utiliser : `"%llu"`). Ce type se manipule comme le type ‘int’ classique

## Partie 1 – Calcul de clés RSA
#### Alice (ou Bob) doit d’abord créer des clés RSA avant de pouvoir échanger des messages.

Pour ce faire, il faut :
1. Choisir deux nombres premiers différents, que nous nommerons *p* et *q*

   - *Fonctions à écrire* (dans un module arithmetic.c / arithmetic.h)
    >Une fonction qui indique si un nombre n est premier
    >
    >Une fonction qui produit un nombre premier entre 300 et 700 (on utilisera la fonction précédente). Il faudra l’appeler autant que nécessaire pour obtenir deux nombres premiers différents.

2. Calculer le produit p*q, appelé n : n est une partie de la clé


3. Calculer le produit (p-1).(q-1), que l’on appellera phi_n


4. Choisir un entier e qui doit être premier avec phi_n (leur pgcd est égal à 1)
   - *Fonction à écrire :*
   >Une fonction qui calcule le pgcd de deux nombres a et b,
   > 
   > Une fonction qui retourne un entier e qui est premier avec phi_n (en choisissant e au hasard, ou avec la fonction qui produit un nombre premier, puis en vérifiant si son pgcd avec phi_n est bien égal à 1)

5. Calculer l’entier d (unique) qui a la propriété suivante : e*d modulo phi_n = 1
   - *Fonction à écrire* (choisissez la version)
    >*Version simple* :  une fonction avec une boucle, qui teste un entier d entre 2 et phi_n-1,  et qui s’arrête quand (e*d)%phi_n == 1. Si p,q, et e sont bien choisis, on obtient toujours une valeur de d valide
    >
    >*Version sophistiquée* : utiliser l’algorithme d’euclide étendu avec e et phi_n, pour trouver la valeur de d

#### Dans le module RSA.c / RSA.h

6. utiliser la structure t_key qui contient tous les éléments d’une clé RSA
    - *fonction à écrire* : 
    >une fonction qui génère tous les éléments d’une clé RSA et retourne une structure t_key complètement initialisée.
    >
    >cette fonction doit avoir pour paramètres les bornes inférieure et supérieure pour les nombres premiers p et q (ici, 300 et 700)



**Exemple**
On choisit au hasard deux nombres premiers distincts  : p = 313 et q = 601

On calcule n = p*q = 188 113     et phi_n = (p-1)*(q-1) = 312*600 = 187 200

On choisit e = 37, on vérifie bien que e et phi_n sont premiers entre eux

On doit maintenant trouver d tel que (d*e)%phi_n = 1 . après calcul, on obtient d = 65 773

On dispose donc de la clé complète avec p,q,n,e,d :

>p= 313
>
>q= 601
>
>n= 188113
>
>e= 37
> 
>d= 65773

 
## Partie 2 : chiffrement et déchiffrement
Pour cette partie, vous allez échanger des clés publique par groupe de 2 : 
chacun produit une clé complète et communique à son binôme sa clé publique

La clé publique est constituée du couple *(n,e)* parmi les valeurs de la clé générée.

Exemple : Vous générez une clé (la même que celle donnée en exemple), et vous publiez *(n,e)=(188133,37)*

Toute personne qui dispose de ces valeurs *(n,e)* peut vous envoyer un message chiffré que vous êtes le seul à pouvoir déchiffrer.

#### Formule de chiffrement (dans RSA.c / RSA.h)

Pour chiffrer un message m (un entier), plus petit que n, on calcule m^e[n] (exponentiation modulaire)

On vous fournit la fonction **modexp**, qui effectue ce calcul de manière très efficace.

> Expliquez comment cette fonction effectue le calcul demandé (vous devez être capable d’expliquer et d’illustrer)

#### Formule de déchiffrement :

Soit c un message chiffré (avec votre clé publique) qui vous parvient.

Pour le déchiffrer, il suffit de calculer c^d[n], où d est votre clé privée

Vous retrouvez alors le message ‘en clair’ m que votre correspondant souhaitait vous faire parvenir.

1. chiffrement et déchiffrement d’un message entier
    - *fonctions à écrire* (dans RSA.c / RSA.h)
    > une fonction qui fait le chiffrement d’un message entier m, avec une clé publique (n,e)
    >
    > une fonction qui fait le déchiffrement d’un message entier c, avec une clé _tRSA_keys


## Partie 3 : application à des messages texte (dans main.c)

Chiffrer des entiers ne permet pas d’illustrer la méthode RSA de manière parlante. 

Aussi, vous disposez du module **‘encoding’** : encoding.c et encoding.h, qui vous permet de :

-	transformer un texte en une suite de nombres entiers (un tableau de nombres entiers)
-	transformer une suite d’entier (un tableau) en un texte, en effectuant l’opération inverse
-	afficher un tableau de nombres entiers correspondant à un codage
-	saisir une suite de nombres entiers, rangée dans un tableau

#### Scénario d’utilisation, pour un binôme Alice et Bob
>Alice génère une clé et obtient les valeurs *p,q,n,e,d*
> 
>Elle communique à Bob sa clé publique : n et e
> 
>Bob choisit un message (texte) à envoyer à Alice.
> 
>Il le convertit en suite de nombres
> 
>Il chiffre chacun de ces nombres avec la clé publique d’Alice.
> 
>Il envoie à Alice la suite des nombres obtenue après chiffrement
> 
>Alice saisit cette suite de nombres
> 
>Elle déchiffre chacun de ces nombres avec sa clé privée : n et d
> 
>Elle convertit cette suite de nombres, obtenue après déchiffrement, en texte
> 
>On compare ensuite le résultat pour voir si la méthode a bien été implémentée.

#### A vous de mettre en place ce scénario, avec chacun son programme principal



