#include <stdint.h>

#include <ijon/ijon.h>

#include "rot.h"

#define C1 0x1763af12
#define C2 0xd1bb5770
#define C3 0x2b3a55bb

// One-third of the f perfmutation
void _ijon_keyexp_fot(uint32_t* _a, uint32_t* _b, uint32_t* _c) {
    uint32_t a = *_a, b = *_b, c = *_c;

    // Application of constants
    a ^= C1;
    b ^= C2;
    c ^= C3;

    // ARX
    c += a;
    a = ROTR(a, 9);

    b ^= c;
    c = ROTR(c, 16);

    a += b;

    c ^= a;
    a = ROTR(a, 17);

    b += c;
    c = ROTR(c, 8);

    // Rotate one word to the right
    *_a = b;
    *_b = c;
    *_c = a;
}

// Number of iterations of f per sponge stage
#define F_ABSORB 4
#define F_MIXING 24
#define F_SQUEEZ 12

void ijon_key_expand(uint8_t const* _key, uint8_t* _key_exp) {
    uint32_t const* key = (uint32_t const*) _key;
    uint32_t* key_exp = (uint32_t*) _key_exp;

    // Initial state of the sponge = 0x0
    uint32_t a = 0, b = 0, c = 0;

    // Absorbing stage
    for(int i = 0; i < IJON_KEY_BYTES / 4; i++) {
        a ^= key[i];

        for(int j = 0; j < F_ABSORB * 3; j++)
            _ijon_keyexp_fot(&a, &b, &c);
    }

    // Middle
    for(int i = 0; i < F_MIXING * 3; i++)
        _ijon_keyexp_fot(&a, &b, &c);

    // Squeezing
    for(int i = 0; i < IJON_KEY_BYTES_EXPANDED / 4 ; i++) {
        for(int j = 0; j < F_SQUEEZ * 3; j++)
            _ijon_keyexp_fot(&a, &b, &c);

        key_exp[i] = a;
    }
}
