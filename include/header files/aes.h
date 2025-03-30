#ifndef MODULE_H 
#define MODULE_H

#include <stdint.h> 
#include <stddef.h> 


unsigned char* convert_to_ascii(const char* message, size_t* length);
unsigned char** create_blocks(const unsigned char ascii_array, size_t array_size, size_t* block_count);

void rot_word(unsigned char* word);
void sub_word(unsigned char* word);
void key_expansion(const unsigned char* main_key, unsigned char* round_keys);

void AddRoundKey(unsigned char **state, unsigned char **roundKeys, int round);
void SubBytes(unsigned char ***state, int numBlocks);
void ShiftRows(unsigned char*** state, size_t block_count);

unsigned char galoisMultiplication(unsigned char a, unsigned char b);
void mixColumns(unsigned char*** state, size_t blockCount);

void aesEncrypt(unsigned char** state, unsigned char* roundKeys, size_t blockCount);

void invShiftRows(unsigned char*** blocks, size_t blockIndex);
void invSubBytes(unsigned char*** blocks, size_t blockIndex);
void invMixColumns(unsigned char*** blocks, size_t blockIndex);

void aesDecrypt(unsigned char** blocks, size_t blockCount, unsigned char* roundKeys);

#endif