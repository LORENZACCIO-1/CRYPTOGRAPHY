#include <stdio.h>
#include "aes.h"
#include "des.h"
#include "rsa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aes.h"

int main() {
    // Étape 1 : Message d'entrée
    const char* message = "This is a secret message!";
    size_t length = 0;

    // Étape 2 : Conversion en ASCII
    unsigned char* ascii_message = convert_to_ascii(message, &length);
    if (!ascii_message) {
        fprintf(stderr, "Erreur lors de la conversion en ASCII.\n");
        return 1;
    }

    // Affichage des valeurs ASCII pour vérification
    printf("Message converti en ASCII (en octets) :\n");
    size_t i;
    for ( i = 0; i < length; i++) {
        printf("%02X ", ascii_message[i]);
    }
    printf("\n");

    // Étape 3 : Génération des blocs de 16 octets
    size_t block_count = 0;
    unsigned char*** blocks = create_blocks(ascii_message, length, &block_count);
    if (!blocks) {
        fprintf(stderr, "Erreur lors de la création des blocs.\n");
        free(ascii_message);
        return 1;
    }

    printf("Nombre de blocs générés : %zu\n", block_count);

    // Étape 4 : Génération des clés secondaires
    unsigned char round_keys[11][4][4]; // 10 tours + clé principale
    const unsigned char key[16] = {
        0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6,
        0xAB, 0xF7, 0xCF, 0xF4, 0x9C, 0x24, 0x12, 0x06
    };
    key_expansion(key, round_keys);

    // Étape 5 : Chiffrement des blocs
    printf("\n--- Chiffrement des blocs ---\n");
    for ( i = 0; i < block_count; i++) {
        encrypt_block(blocks[i], round_keys);
    }

    printf("Message chiffré :\n");
    for (i = 0; i < block_count; i++) {
    	int row;
        for ( row = 0; row < 4; row++) {
        	int col;
            for ( col = 0; col < 4; col++) {
                printf("%02X ", blocks[i][row][col]);
            }
        }
        printf("\n");
    }

    // Étape 6 : Décryptage des blocs
    printf("\n--- Décryptage des blocs ---\n");
    for ( i = 0; i < block_count; i++) {
        decrypt_block(blocks[i], round_keys);
    }

    printf("Message déchiffré (en ASCII) :\n");
    for ( i = 0; i < block_count; i++) {
    	int row,col;
        for (row = 0; row < 4; row++) {
            for ( col = 0; col < 4; col++) {
                printf("%c", blocks[i][row][col]);
            }
        }
    }
    printf("\n");

    // Libération de la mémoire
    free(ascii_message);
    free_blocks(blocks, block_count);

   










    uint64_t p = 61; // Nombre premier
    uint64_t q = 53; // Nombre premier
    uint64_t n, e, d;

    // Générer les clés
    generate_keys(&e, &d, &n, p, q);

    printf("Clé publique: (e = %llu, n = %llu)\n", e, n);
    printf("Clé privée: (d = %llu, n = %llu)\n", d, n);

    uint64_t message = 65; // Message à chiffrer (en entier)
    printf("Message original: %llu\n", message);

    // Chiffrement
    uint64_t cipher = encrypt(message, e, n);
    printf("Message chiffré: %llu\n", cipher);

    // Déchiffrement
    uint64_t decrypted = decrypt(cipher, d, n);
    printf("Message déchiffré: %llu\n", decrypted);
    
    
    
    
    
    
    
    
    
    
    
    
  



#define BLOCK_SIZE 64
#define HALF_BLOCK_SIZE 32
#define SUBKEY_SIZE 48
#define NUM_ROUNDS 16

int IP[BLOCK_SIZE] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

int PI[BLOCK_SIZE] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

int E[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

int P[HALF_BLOCK_SIZE] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};

int PC1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

int PC2[48] = {
    14, 17, 11, 24, 1, 5, 3, 28,
    15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
};

int S[8][4][16] = {
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    }
};

int iteration_shift[NUM_ROUNDS] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};


    int plaintext[64] = {
        0, 0, 0, 1, 0, 0, 1, 1,
        0, 1, 0, 1, 1, 1, 1, 0,
        1, 0, 0, 0, 1, 0, 1, 0,
        1, 0, 1, 1, 0, 1, 1, 1,
        1, 1, 1, 0, 1, 0, 0, 0,
        1, 1, 0, 0, 0, 1, 1, 1,
        0, 0, 1, 0, 1, 1, 0, 1,
        0, 1, 1, 1, 0, 1, 1, 0
    };

    int key[64] = {
        0, 0, 0, 1, 0, 0, 1, 1,
        0, 1, 0, 1, 1, 1, 1, 0,
        1, 0, 0, 0, 1, 0, 1, 0,
        1, 0, 1, 1, 0, 1, 1, 1,
        1, 1, 1, 0, 1, 0, 0, 0,
        1, 1, 0, 0, 0, 1, 1, 1,
        0, 0, 1, 0, 1, 1, 0, 1,
        0, 1, 1, 1, 0, 1, 1, 0
    };

    int ciphertext[64];

    des(plaintext, key, ciphertext, 1);

    printf("Texte chiffré :\n");
    for (int i = 0; i < 64; i++) {
        printf("%d", ciphertext[i]);
    }
    printf("\n");

    return 0;
}



 
