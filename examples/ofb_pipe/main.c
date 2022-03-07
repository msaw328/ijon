#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ofb.h"

int main(int argc, char** argv) {
    // check cmd line arguments
    if(argc < 2) {
        printf("Usage: %s [keyfile] [options]\n", argv[0]);
        printf("%s\n", "Options:");
        printf("%s\n\n", "   -d\tdecrypt instead of encrypting");
        puts("When encrypting, first 16 bytes SENT is IV (generated randomly)");
        puts("When decrypting, first 16 bytes RECEIVED is IV");
        exit(0);
    }

    int is_encrypting;

    if(argc > 2) {
        if(strncmp(argv[2], "-d", 2) != 0) {
            printf("Unknown argument \"%s\"\n", argv[2]);
            exit(0);
        }

        is_encrypting = 0;
    } else {
        is_encrypting = 1;
    }

    // read keyfile
    uint8_t key[16] = { 0 };
    if(access(argv[1], R_OK) != 0) {
        perror("Error while trying to access() the keyfile");
        exit(0);
    }

    int keyfile_fd = open(argv[1], O_RDONLY);
    ssize_t nbytes = read(keyfile_fd, key, 16);

    if(nbytes < 16) {
        printf("Keyfile \"%s\" too short: only %ld bytes read (16 required)\n", argv[1], nbytes);
        exit(0);
    }

    close(keyfile_fd);

    // Generate and write or read IV based on encryption/decryption being performed
    uint8_t IV[16];
    if(is_encrypting) {
        OFB_gen_rand_IV(IV);
        write(STDOUT_FILENO, IV, 16);
    } else {
        read(STDIN_FILENO, IV, 16);
    }

    // Init OFB context
    OFB_ctx_t ctx = { 0 };
    OFB_init(&ctx, key, IV);


    // loop
    uint8_t input_buffer[16] = { 0 };
    uint8_t output_buffer[16] = { 0 };

    while((nbytes = read(STDIN_FILENO, input_buffer, 16))) {
        OFB_xor_bytes(&ctx, input_buffer, output_buffer, (size_t) nbytes);
        write(STDOUT_FILENO, output_buffer, (size_t) nbytes);
    }
}
