#ifndef RSA_H
#define RSA_H

#include <stdlib.h>
#include <stdint.h>


void generate_keys(uint64_t* e, uint64_t* d, uint64_t* n, uint64_t p, uint64_t q);


uint64_t encrypt(uint64_t message, uint64_t e, uint64_t n);


uint64_t decrypt(uint64_t cipher, uint64_t d, uint64_t n);


uint64_t gcd(uint64_t a, uint64_t b);
uint64_t mod_inverse(uint64_t a, uint64_t m);
uint64_t mod_exp(uint64_t base, uint64_t exp, uint64_t mod);

#endif