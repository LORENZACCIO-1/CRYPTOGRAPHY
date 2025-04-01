===================================================
            Projet de Cryptographie : AES, DES & RSA
===================================================
Auteur : Mohamed Taha Aboumehdi Hassani, Wadie Kadiri  
Date : Décembre 2024  
===================================================

-----------------
Présentation du Projet
-----------------
Ce projet implémente trois algorithmes de cryptographie :

1. **AES (Advanced Encryption Standard)** :
   - Algorithme de chiffrement par blocs avec des clés symétriques (128, 192 ou 256 bits).
   - Fonctionnalités incluses :  
     - Génération des sous-clés  
     - Chiffrement  
     - Déchiffrement  

2. **DES (Data Encryption Standard)** :
   - Algorithme symétrique basé sur la structure de Feistel utilisant 16 tours pour le chiffrement par blocs.
   - Fonctionnalités incluses :  
     - Chiffrement par blocs  
     - Déchiffrement par blocs  

3. **RSA (Rivest–Shamir–Adleman)** :
   - Algorithme asymétrique de chiffrement utilisant une clé publique/privée pour la transmission sécurisée des données.
   - Fonctionnalités incluses :  
     - Génération de clés publiques et privées  
     - Chiffrement des messages  
     - Déchiffrement des messages  

Le projet propose un programme principal pour démontrer l'utilisation pratique de ces trois algorithmes avec des exemples concrets.

===================================================

-----------------
Structure des Fichiers
-----------------
1. **aes.h / aes.c**  
   - Contient l'implémentation complète de l'algorithme AES, avec :  
     - Génération de sous-clés  
     - Fonctionnalités de chiffrement et déchiffrement  

2. **des.h / des.c**  
   - Implémente l'algorithme DES avec :  
     - Chiffrement par blocs  
     - Déchiffrement par blocs  

3. **rsa.h / rsa.c**  
   - Implémente l'algorithme RSA avec :  
     - Génération de clés  
     - Chiffrement et déchiffrement des messages  

4. **main.c**  
   - Démonstration pratique de l'utilisation des algorithmes AES, DES et RSA avec des exemples concrets.  

5. **Makefile**  
   - Facilite la compilation du projet avec les commandes suivantes :  
     - `make` : Compile l'ensemble du projet  
     - `make clean` : Supprime les fichiers intermédiaires et l'exécutable  

===================================================

-----------------
Instructions
-----------------
1. **Compilation** :
   - Assurez-vous que tous les fichiers `.c`, `.h` et le `Makefile` sont dans le même répertoire.
   

2. **Exécution** :
   - Après la compilation, un fichier exécutable sera généré (par exemple, `rsa_des_aes`).  
 

3. **Nettoyage** :
  

===================================================

-----------------
Exemple de Résultat
-----------------
**AES :**  
- Texte clair : `101010...`  
- Texte chiffré : `111000...`  

**DES :**  
- Texte clair : `01010101...`  
- Texte chiffré : `11001100...`  

**RSA :**  
- Clé publique : (e = 17, n = 3233)  
- Clé privée : (d = 413, n = 3233)  
- Message original : `65`  
- Message chiffré : `2790`  
- Message déchiffré : `65`  

===================================================

-----------------
Dépendances
-----------------
- Ce projet utilise uniquement la bibliothèque standard C (`stdio.h`, `stdlib.h`, `string.h`).  
- Aucun autre outil externe n'est nécessaire.  

===================================================

-----------------
Prochaines Étapes
-----------------
1. Étendre le support pour des tailles de clé RSA plus importantes.  
2. Implémenter le mode CBC pour l'algorithme DES.  
3. Ajouter un ensemble de tests automatisés pour valider toutes les fonctions implémentées.  
