#ifndef _IJON_SPN_H_
#define _IJON_SPN_H_

// Internal substitution-permutation network functions
//
// Declarations of S-BOX, P-BOX and their inverses

#include <stdint.h>

void _ijon_sbox(uint32_t* x, uint32_t* y);
void _ijon_sbox_inv(uint32_t* x, uint32_t* y);

void _ijon_pbox(uint32_t* x, uint32_t* y, uint32_t* z, uint32_t* w);
void _ijon_pbox_inv(uint32_t* x, uint32_t* y, uint32_t* z, uint32_t* w);

#endif
