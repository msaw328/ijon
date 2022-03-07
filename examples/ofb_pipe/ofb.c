#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <ijon/ijon.h>

#include "ofb.h"

void _next_keystream_block(OFB_ctx_t* c) {
    uint8_t tmp[IJON_BLOCK_BYTES];
    ijon_encrypt_block(c->keystream_block, c->keysched, tmp);
    memcpy(c->keystream_block, tmp, IJON_BLOCK_BYTES);
}

void OFB_init(OFB_ctx_t* c, uint8_t* key, uint8_t* iv) {
    // IV
    memcpy(c->IV, iv, IJON_BLOCK_BYTES);

    // key
    ijon_key_expand(key, c->keysched);

    // keystream block
    ijon_encrypt_block(c->IV, c->keysched, c->keystream_block);

    c->bytes_used = 0;
}

void OFB_xor_bytes(OFB_ctx_t* c, uint8_t* src, uint8_t* dst, size_t n) {
    unsigned int count = 0;

    while(count < n) {
        dst[count] = src[count] ^ c->keystream_block[c->bytes_used];

        count++;
        c->bytes_used++;

        if(c->bytes_used >= 16) {
            _next_keystream_block(c);
            c->bytes_used = 0;
        }
    }
}

void OFB_gen_rand_IV(uint8_t* iv) {
    int rand_fd = open("/dev/urandom", O_RDONLY);
    read(rand_fd, iv, IJON_BLOCK_BYTES);
    close(rand_fd);
}
