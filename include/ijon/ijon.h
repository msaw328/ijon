#ifndef _IJON_PUBLIC_INCLUDE_H_
#define _IJON_PUBLIC_INCLUDE_H_

// libijon public API

#include <stdint.h>

#define IJON_BLOCK_BYTES 16
#define IJON_KEY_BYTES 16
#define IJON_STEPS 10
#define IJON_KEY_BYTES_EXPANDED (8 * 4 * IJON_STEPS)


// Key expansion
//
// IN:  key         - pointer to 16-byte long buffer of key material (readonly)
// OUT: key_exp     - pointer to 320-byte long buffer, that the sub-keys will be written to
void ijon_key_expand(uint8_t const* key, uint8_t* key_exp);


// Encryption
//
// IN:  plaintext   - pointer to 16-byte long buffer of data (readonly)
// IN:  key_exp     - pointer to 320-byte long buffer containing the sub-keys (readonly)
// OUT: ciphertext  - pointer to 16-byte long buffer to which the encrypted data will be written
void ijon_encrypt_block(uint8_t const* plaintext, uint8_t const* key_exp, uint8_t* ciphertext);


// Decryption
//
// IN:  ciphertext  - pointer to 16-byte long buffer of encrypted data (readonly)
// IN:  key_exp     - pointer to 320-byte long buffer containing the sub-keys (readonly)
// OUT: plaintext   - pointer to 16-byte long buffer to which the decrypted data will be written
void ijon_decrypt_block(uint8_t const* ciphertext, uint8_t const* key_exp, uint8_t* plaintext);

#endif
