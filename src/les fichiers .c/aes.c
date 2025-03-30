[11:52, 15/12/2024] Wadie Pirate: #include "module.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const unsigned char s_box[256] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};
const unsigned char InvSBox[16][16] = {
    {0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB},
    {0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB},
    {0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E},
    {0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25},
    {0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92},
    {0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84},
    {0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06},
    {0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B},
    {0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73},
    {0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E},
    {0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B},
    {0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4},
    {0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F},
    {0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF},
    {0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61},
    {0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D}
};
static const unsigned char rcon[11] = {
    0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
};
const unsigned char MixColumnsMatrix[4][4] = {
    {0x02, 0x03, 0x01, 0x01},
    {0x01, 0x02, 0x03, 0x01},
    {0x01, 0x01, 0x02, 0x03},
    {0x03, 0x01, 0x01, 0x02}
};
const unsigned char InvMixColumnsMatrix[4][4] = {
    {0x0E, 0x0B, 0x0D, 0x09},
    {0x09, 0x0E, 0x0B, 0x0D},
    {0x0D, 0x09, 0x0E, 0x0B},
    {0x0B, 0x0D, 0x09, 0x0E}
};
size_t i,b,j,block;

unsigned char* convert_to_ascii(const char* message, size_t* length) {
	
    if (message == NULL) {
        fprintf(stderr, "Erreur : le message est NULL\n");
        exit(1);
    }

    
    *length = strlen(message);

  
    unsigned char* ascii_array = (unsigned char*)malloc(*length * sizeof(unsigned char));
    if (ascii_array == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(1);
    }

   
    
    for ( i = 0; i < *length; i++) {
        ascii_array[i] = (unsigned char)message[i];
    }

    return ascii_array;  
}

unsigned char** create_blocks(const unsigned char ascii_array, size_t array_size, size_t* block_count) {
    
    *block_count = (array_size + 15) / 16;

  
    unsigned char** blocks = malloc(*block_count * sizeof(unsigned char*));
    if (!blocks) {
        fprintf(stderr, "Erreur : Allocation mémoire pour les blocs échouée\n");
        exit(1);
    }

    
    for ( b = 0; b < *block_count; ++b) {
        
        blocks[b] = malloc(4 * sizeof(unsigned char*));
        if (!blocks[b]) {
            fprintf(stderr, "Erreur : Allocation mémoire pour un bloc échouée\n");
            exit(1);
        }
        for (i = 0; i < 4; ++i) {
            blocks[b][i] = malloc(4 * sizeof(unsigned char));
            if (!blocks[b][i]) {
                fprintf(stderr, "Erreur : Allocation mémoire pour une ligne du bloc échouée\n");
                exit(1);
            }
        }

        
        for ( i = 0; i < 4; ++i) {
            for ( j = 0; j < 4; ++j) {
                size_t index = b * 16 + i * 4 + j;
                if (index < array_size) {
                    blocks[b][i][j] = ascii_array[index];
                } else {
                    blocks[b][i][j] = 0x00; // Padding
                }
            }
        }
    }

    return blocks;
}

void rot_word(unsigned char* word) {
    unsigned char temp = word[0];
    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = temp;
}

void sub_word(unsigned char* word) {
	int k;
    for (k = 0; k < 4; k++) {
        word[k] = s_box[word[k]];
    }
}

void key_expansion(const unsigned char* main_key, unsigned char* round_keys) {
    unsigned char temp[4];
    int i,j;

    
    for (i = 0; i < 16; i++) {
        round_keys[i] = main_key[i];
    }

    
    for (i = 16; i < 176; i += 4) {
        
        for (j = 0; j < 4; j++) {
            temp[j] = round_keys[i - 4 + j];
        }

        
        if (i % 16 == 0) {
            rot_word(temp);                
            sub_word(temp);                
            temp[0] ^= rcon[i / 16];       
        }

       
        for ( j = 0; j < 4; j++) {
            round_keys[i + j] = round_keys[i - 16 + j] ^ temp[j];
        }
    }
}

void AddRoundKey(unsigned char **state, unsigned char **roundKeys, int round) {
	int i,j;
    for (i = 0; i < 4; i++) {
        for ( j = 0; j < 4; j++) {
            state[round][i][j] ^= roundKeys[round][i][j];
        }
    }
}

void SubBytes(unsigned char ***state, int numBlocks) {
    
    int block,i,j;
    for ( block = 0; block < numBlocks; block++) { 
        for (i = 0; i < 4; i++) { 
            for ( j = 0; j < 4; j++) { 
                state[block][i][j] =s_box[state[block][i][j] / 0x10][state[block][i][j] % 0x10];
            }
        }
    }
}

void ShiftRows(unsigned char*** state, size_t block_count) {
	size_t block;
    for ( block = 0; block < block_count; block++) {
        // Parcourir chaque bloc
        for ( i = 1; i < 4; i++) {
            // Décalage circulaire à gauche de la ième ligne
            unsigned char temp[4];
            for ( j = 0; j < 4; j++) {
                temp[j] = state[block][i][(j + i) % 4];
            }
            // Copier les valeurs décalées dans la ligne
            for ( j = 0; j < 4; j++) {
                state[block][i][j] = temp[j];
            }
        }
    }
}

unsigned char galoisMultiplication(unsigned char a, unsigned char b) {
    unsigned char p = 0;
    unsigned char hi_bit_set;
	int i;
    for (i = 0; i < 8; i++) {
        if (b & 1) {
            p ^= a;
        }

        hi_bit_set = a & 0x80;
        a <<= 1;

        if (hi_bit_set) {
            a ^= 0x1b; 
        }

        b >>= 1;
    }

    return p;
}

void mixColumns(unsigned char*** state, size_t blockCount) {
	int col,i,j;
    for ( block = 0; block < blockCount; block++) {
        for ( col = 0; col < 4; col++) {
            unsigned char temp[BLOCK_SIZE] = {0};

            for ( i = 0; i < BLOCK_SIZE; i++) {
                for ( j = 0; j < BLOCK_SIZE; j++) {
                    temp[i] ^= galoisMultiplication(MixColumnsMatrix[i][j], (*state)[block][j][col]);
                }
            }

            
            for ( i = 0; i < BLOCK_SIZE; i++) {
                (*state)[block][i][col] = temp[i];
            }
        }
    }
}

void aesEncrypt(unsigned char** state, unsigned char* roundKeys, size_t blockCount) {
   
    for ( block = 0; block < blockCount; ++block) {
        addRoundKey(state, roundKeys, blockCount);
    }

    
    int round;
    for (round = 1; round <= 9; ++round) {
        for ( block = 0; block < blockCount; ++block) {
            subBytes(state[block]);
            shiftRows(state[block]);
            mixColumns(state[block]);
            addRoundKey(state, &roundKeys[round * 4], blockCount); 
        }
    }

   
    for (block = 0; block < blockCount; ++block) {
        subBytes(state[block]);
        shiftRows(state[block]);
        addRoundKey(state, &roundKeys[40], blockCount); 
    }
}

void invShiftRows(unsigned char*** blocks, size_t blockIndex) {
    unsigned char temp;
    unsigned char (state)[4] = (unsigned char()[4])blocks[blockIndex];

    
    temp = state[1][3];
    int col;
    for (col = 3; col > 0; --col) {
        state[1][col] = state[1][col - 1];
    }
    state[1][0] = temp;

   
    unsigned char temp1 = state[2][2];
    unsigned char temp2 = state[2][3];
    state[2][3] = state[2][1];
    state[2][2] = state[2][0];
    state[2][1] = temp2;
    state[2][0] = temp1;

    
    temp = state[3][0];
    for ( col = 0; col < 3; ++col) {
        state[3][col] = state[3][col + 1];
    }
    state[3][3] = temp;
}

void invSubBytes(unsigned char*** blocks, size_t blockIndex) {
    unsigned char (state)[4] = (unsigned char()[4])blocks[blockIndex];
	int i,j;
    for ( i = 0; i < 4; ++i) {
        for ( j = 0; j < 4; ++j) {
            state[i][j] = InvSBox[state[i][j] / 0x10][state[i][j] % 0x10];
        }
    }
}

void invMixColumns(unsigned char*** blocks, size_t blockIndex) {
    unsigned char temp[4];
    unsigned char (state)[4] = (unsigned char()[4])blocks[blockIndex];
	int col,row;
    for ( col = 0; col < 4; ++col) {
        temp[0] = galoisMult(state[0][col], 0x0E) ^
                  galoisMult(state[1][col], 0x0B) ^
                  galoisMult(state[2][col], 0x0D) ^
                  galoisMult(state[3][col], 0x09);

        temp[1] = galoisMult(state[0][col], 0x09) ^
                  galoisMult(state[1][col], 0x0E) ^
                  galoisMult(state[2][col], 0x0B) ^
                  galoisMult(state[3][col], 0x0D);

        temp[2] = galoisMult(state[0][col], 0x0D) ^
                  galoisMult(state[1][col], 0x09) ^
                  galoisMult(state[2][col], 0x0E) ^
                  galoisMult(state[3][col], 0x0B);

        temp[3] = galoisMult(state[0][col], 0x0B) ^
                  galoisMult(state[1][col], 0x0D) ^
                  galoisMult(state[2][col], 0x09) ^
                  galoisMult(state[3][col], 0x0E);

        for (row = 0; row < 4; ++row) {
            state[row][col] = temp[row];
        }
    }
}

void aesDecrypt(unsigned char** blocks, size_t blockCount, unsigned char* roundKeys) {
	size_t blockIndex ;
    for ( blockIndex = 0; blockIndex < blockCount; ++blockIndex) {
       
        addRoundKey(blocks, roundKeys[40], blockIndex);

        
        int round;
        for ( round = 9; round >= 1; --round) {
            invShiftRows(blocks, blockIndex);
            invSubBytes(blocks, blockIndex);
            addRoundKey(blocks, roundKeys[round * 4], blockIndex);
            invMixColumns(blocks, blockIndex);
        }

        
        invShiftRows(blocks, blockIndex);
        invSubBytes(blocks, blockIndex);
        addRoundKey(blocks, roundKeys[0], blockIndex); 
    }
}
[11:53, 15/12/2024] Wadie Pirate: #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "module.h"

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

    return 0;
}