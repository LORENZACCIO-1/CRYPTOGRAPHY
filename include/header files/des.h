#ifndef DES_H
#define DES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BYTE_SIZE 8
#define BLOCK_SIZE 64
#define HALF_BLOCK_SIZE 32
#define SUBKEY_SIZE 48
#define NUM_ROUNDS 16


extern int IP[BLOCK_SIZE];
extern int PI[BLOCK_SIZE];
extern int E[48];
extern int P[HALF_BLOCK_SIZE];
extern int PC1[56];
extern int PC2[48];
extern int S[8][4][16];
extern int iteration_shift[NUM_ROUNDS];


void permute(int *input, int *output, int *table, int n);
void rotate_left(int *key, int shifts, int size);
void xor(int *a, int *b, int *result, int size);
void sbox_substitution(int *input, int *output);


void generate_subkeys(int *key, int subkeys[NUM_ROUNDS][SUBKEY_SIZE]);


void function_f(int *R, int *subkey, int *output);


void des(int *plaintext, int *key, int *ciphertext, int mode);

#endif 
