#ifndef _IJON_ROT_H_
#define _IJON_ROT_H_

// Rotations in both directions implemented in C
//
// IJON uses only rotations to the right, so ROTL is commented out
//
// Compiler optimizations are usually smart enough to notice that this series of operations implements a rotation
// If this is not the case, optimized implementations should use inline assembly for rotations instead

//#define ROTL(val, shift) ((val << shift) | (val >> (sizeof(val) * 8 - shift)))
#define ROTR(val, shift) ((val >> shift) | (val << (sizeof(val) * 8 - shift)))

#endif
