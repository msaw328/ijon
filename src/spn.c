#include <stdint.h>

#include <ijon/ijon.h>

#include "rot.h"
#include "spn.h"

// Alzette S-BOX
#define SBOX_C 0xb7e15162
void _ijon_sbox(uint32_t* _x, uint32_t* _y) {
    uint32_t x = *_x, y = *_y;

    y += ROTR(x, 31);
    x ^= ROTR(y, 24);

    y ^= SBOX_C;

    y += ROTR(x, 17);
    x ^= ROTR(y, 17);

    y ^= SBOX_C;

    y += x;
    x ^= ROTR(y, 31);

    y ^= SBOX_C;
    
    y += ROTR(x, 23);
    x ^= ROTR(y, 16);

    y ^= SBOX_C;

    *_x = x;
    *_y = y;
}

void _ijon_sbox_inv(uint32_t* _x, uint32_t* _y) {
    uint32_t x = *_x, y = *_y;

    y ^= SBOX_C;

    x ^= ROTR(y, 16);
    y -= ROTR(x, 23);

    y ^= SBOX_C;

    x ^= ROTR(y, 31);
    y -= x;

    y ^= SBOX_C;

    x ^= ROTR(y, 17);
    y -= ROTR(x, 17);

    y ^= SBOX_C;

    x ^= ROTR(y, 24);
    y -= ROTR(x, 31);

    *_x = x;
    *_y = y;
}

// The F function used within the Feistel-like linear layer
void _ijon_pbox_feistel_f(uint32_t* _a, uint32_t* _b) {
    uint32_t a = *_a, b = *_b;

    uint32_t tmp = ROTR(a ^ b, 7);
    *_a = a ^ tmp;
    *_b = b ^ tmp;
}

void _ijon_pbox(uint32_t* _x, uint32_t* _y, uint32_t* _z, uint32_t* _w) {
    uint32_t x = *_x, y = *_y, z = *_z, w = *_w;

    uint32_t a = x, b = y;
    _ijon_pbox_feistel_f(&a, &b);

    *_x = z ^ a;
    *_y = w ^ b;
    *_z = x;
    *_w = y;
}

void _ijon_pbox_inv(uint32_t* _x, uint32_t* _y, uint32_t* _z, uint32_t* _w) {
    uint32_t x = *_x, y = *_y, z = *_z, w = *_w;

    uint32_t a = z, b = w;
    _ijon_pbox_feistel_f(&a, &b);

    *_x = z;
    *_y = w;
    *_z = x ^ a;
    *_w = y ^ b;
}
