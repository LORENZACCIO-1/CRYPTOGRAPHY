[12:55, 15/12/2024] Wadie Pirate: #include "rsa.h"
#include <stdio.h>


uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

uint64_t mod_inverse(uint64_t a, uint64_t m) {
    uint64_t m0 = m, t, q;
    uint64_t x0 = 0, x1 = 1;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    return (x1 + m0) % m0;
}

uint64_t mod_exp(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (…
[12:55, 15/12/2024] Wadie Pirate: #include <stdio.h>
#include "rsa.h"

int main() {
    uint64_t p = 61; 
    uint64_t q = 53; 
    uint64_t n, e, d;

    
    generate_keys(&e, &d, &n, p, q);

    printf("Clé publique: (e = %llu, n = %llu)\n", e, n);
    printf("Clé privée: (d = %llu, n = %llu)\n", d, n);

    uint64_t message = 65; 
    printf("Message original: %llu\n", message);

    // Chiffrement
    uint64_t cipher = encrypt(message, e, n);
    printf("Message chiffré: %llu\n", cipher);

    // Déchiffrement
    uint64_t decrypted = decrypt(cipher, d, n);
    printf("Message déchiffré: %llu\n", decrypted);

    return 0;
}