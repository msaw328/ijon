#include <unistd.h>
#include <fcntl.h>

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include <ijon/ijon.h>

void read_random(uint8_t* buff) {
    int fd = open("/dev/urandom", O_RDONLY);
    read(fd, buff, 16);
    close(fd);
}

void print_binary(uint8_t a) {
    write(STDOUT_FILENO, &a, sizeof(a));
}

int main() {
    uint8_t key[IJON_KEY_BYTES] = { 0 };
    read_random(key);

    uint8_t key_exp[IJON_KEY_BYTES_EXPANDED] = { 0 };

    ijon_key_expand(key, key_exp);

    uint8_t plaintext[IJON_BLOCK_BYTES] = { 0 };
    read_random(plaintext);

    uint8_t expected_plaintext[IJON_BLOCK_BYTES] = { 0 };
    memcpy(expected_plaintext, plaintext, IJON_BLOCK_BYTES);

    uint8_t ciphertext[IJON_BLOCK_BYTES] = { 0 };


    // Print the key
    for(int j = 0; j < IJON_KEY_BYTES; j++)
        print_binary(key[j]);

    // Print plaintext in the beginning
    for(int j = 0; j < IJON_BLOCK_BYTES; j++)
        print_binary(plaintext[j]);

    ijon_encrypt_block(plaintext, key_exp, ciphertext);


    // Print resulting ciphertext
    for(int j = 0; j < IJON_BLOCK_BYTES; j++)
        print_binary(ciphertext[j]);

    ijon_decrypt_block(ciphertext, key_exp, plaintext);

    // Print the plaintext after decryption
    for(int j = 0; j < IJON_BLOCK_BYTES; j++)
        print_binary(plaintext[j]);

    if(memcmp(plaintext, expected_plaintext, IJON_BLOCK_BYTES) == 0) { 
        fprintf(stderr, "DECRYPTION OK\n");
    } else {
        fprintf(stderr, "DECRYPTION ERR\n");
    }
}
