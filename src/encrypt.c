#include <stdint.h>
#include <string.h>

#include <ijon/ijon.h>

#include "rot.h"
#include "spn.h"

// x,y,z,w -> words of plaintext
// subkeys -> pointer to the first of 8 subkeys dedicated to this round
void _ijon_encrypt_round(uint32_t* _x, uint32_t* _y, uint32_t* _z, uint32_t* _w, uint32_t const* subkeys) {
    uint32_t x = *_x, y = *_y, z = *_z, w = *_w;

    // First round
    x ^= subkeys[0];
    y ^= subkeys[1];
    z ^= subkeys[2];
    w ^= subkeys[3];

    _ijon_sbox(&x, &y);
    _ijon_sbox(&z, &w);

    // Second round
    x ^= subkeys[4];
    y ^= subkeys[5];
    z ^= subkeys[6];
    w ^= subkeys[7];

    _ijon_sbox(&x, &y);
    _ijon_sbox(&z, &w);

    _ijon_pbox(&x, &y, &z, &w);

    *_x = x;
    *_y = y;
    *_z = z;
    *_w = w;
}

void ijon_encrypt_block(uint8_t const* plaintext, uint8_t const* key_exp, uint8_t* ciphertext) {
    uint32_t const* p = (uint32_t const*) plaintext; // 4 x 32 bit
    uint32_t const* k_exp = (uint32_t const*) key_exp; // 80 x 32 bit
    uint32_t* c = (uint32_t*) ciphertext; // 4 x 32 bit

    // Copy plaintext to state
    uint32_t state[IJON_BLOCK_BYTES / 4];
    memcpy(state, p, IJON_BLOCK_BYTES);

    // Perform 10 steps
    for(int step = 0; step < IJON_STEPS; step++) {
        _ijon_encrypt_round(state + 0, state + 1, state + 2, state + 3, k_exp + (8 * step));
    }

    // Copy state to ciphertext
    memcpy(c, state, IJON_BLOCK_BYTES);
}
