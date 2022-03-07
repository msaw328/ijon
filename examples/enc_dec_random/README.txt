enc_dec_random

This example serves as a basic test of the encryption/decryption functionality.

It generates a random key and plaintext using /dev/urandom, encrypts the plaintext and then decrypts the ciphertext verifying that it produces the same plaintext back.
If it works "DECRYPTION OK" is printed to stderr, otherwise "DECRYPTION ERR" prints.

Key, plaintext, ciphertext and decrypted plaintext are written to the stdout in binary form, and are best viewed using a hex viewer such as hexdump or xxd:

./enc_dec_random | hexdump -C
./enc_dec_random | xxd -g 1
