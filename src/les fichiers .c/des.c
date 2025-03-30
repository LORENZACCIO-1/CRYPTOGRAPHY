#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "des.h"

#define BYTE_SIZE 8
#define BLOCK_SIZE 64
#define HALF_BLOCK_SIZE 32
#define SUBKEY_SIZE 48
#define NUM_ROUNDS 16

// Tables de permutations et S-boxes (simplifiées pour clarté)
int IP[BLOCK_SIZE] = { /* Table IP */ };
int PI[BLOCK_SIZE] = { /* Table inverse IP */ };
int E[48] = { /* Expansion table */ };
int P[HALF_BLOCK_SIZE] = { /* Permutation table */ };
int PC1[56] = { /* Permutation table 1 */ };
int PC2[48] = { /* Permutation table 2 */ };
int S[8][4][16] = { /* S-boxes */ };
int iteration_shift[NUM_ROUNDS] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// Fonctions utilitaires
void permute(int *input, int *output, int *table, int n) {
    for (int i = 0; i < n; i++) {
        output[i] = input[table[i] - 1];
    }
}

void rotate_left(int *key, int shifts, int size) {
    int temp[shifts];
    for (int i = 0; i < shifts; i++) {
        temp[i] = key[i];
    }
    for (int i = 0; i < size - shifts; i++) {
        key[i] = key[i + shifts];
    }
    for (int i = 0; i < shifts; i++) {
        key[size - shifts + i] = temp[i];
    }
}

void xor(int *a, int *b, int *result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = a[i] ^ b[i];
    }
}

void sbox_substitution(int *input, int *output) {
    for (int i = 0; i < 8; i++) {
        int row = (input[i * 6] << 1) | input[i * 6 + 5];
        int col = (input[i * 6 + 1] << 3) | (input[i * 6 + 2] << 2) | (input[i * 6 + 3] << 1) | input[i * 6 + 4];
        int value = S[i][row][col];
        for (int j = 0; j < 4; j++) {
            output[i * 4 + j] = (value >> (3 - j)) & 1;
        }
    }
}

void generate_subkeys(int *key, int subkeys[NUM_ROUNDS][SUBKEY_SIZE]) {
    int permuted_key[56];
    permute(key, permuted_key, PC1, 56);

    int C[28], D[28];
    memcpy(C, permuted_key, 28 * sizeof(int));
    memcpy(D, permuted_key + 28, 28 * sizeof(int));

    for (int i = 0; i < NUM_ROUNDS; i++) {
        rotate_left(C, iteration_shift[i], 28);
        rotate_left(D, iteration_shift[i], 28);

        int combined[56];
        memcpy(combined, C, 28 * sizeof(int));
        memcpy(combined + 28, D, 28 * sizeof(int));

        permute(combined, subkeys[i], PC2, 48);
    }
}

void function_f(int *R, int *subkey, int *output) {
    int expanded_R[48];
    permute(R, expanded_R, E, 48);

    int xor_result[48];
    xor(expanded_R, subkey, xor_result, 48);

    int sbox_output[32];
    sbox_substitution(xor_result, sbox_output);

    permute(sbox_output, output, P, 32);
}

void des(int *plaintext, int *key, int *ciphertext, int mode) {
    int permuted_block[64];
    permute(plaintext, permuted_block, IP, 64);

    int L[32], R[32];
    memcpy(L, permuted_block, 32 * sizeof(int));
    memcpy(R, permuted_block + 32, 32 * sizeof(int));

    int subkeys[NUM_ROUNDS][48];
    generate_subkeys(key, subkeys);

    if (mode == 0) { // Decryption
        for (int i = 0; i < NUM_ROUNDS / 2; i++) {
            int temp[48];
            memcpy(temp, subkeys[i], 48 * sizeof(int));
            memcpy(subkeys[i], subkeys[NUM_ROUNDS - i - 1], 48 * sizeof(int));
            memcpy(subkeys[NUM_ROUNDS - i - 1], temp, 48 * sizeof(int));
        }
    }

    for (int i = 0; i < NUM_ROUNDS; i++) {
        int f_output[32];
        function_f(R, subkeys[i], f_output);

        int new_R[32];
        xor(L, f_output, new_R, 32);

        memcpy(L, R, 32 * sizeof(int));
        memcpy(R, new_R, 32 * sizeof(int));
    }

    int combined[64];
    memcpy(combined, R, 32 * sizeof(int));
    memcpy(combined + 32, L, 32 * sizeof(int));

    permute(combined, ciphertext, PI, 64);
}

int main() {
    // Exemple d'utilisation
    int plaintext[64] = { /* Données binaires */ };
    int key[64] = { /* Clé binaire */ };
    int ciphertext[64];

    des(plaintext, key, ciphertext, 1); // Chiffrement

    printf("Texte chiffré :\n");
    for (int i = 0; i < 64; i++) {
        printf("%d", ciphertext[i]);
    }

    return 0;
}