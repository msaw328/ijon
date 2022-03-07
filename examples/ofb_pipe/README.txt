ofb_pipe

This program reads its standard input and encrypts/decrypts it using
IJON in OFB mode (in OFB enryption and decryption is the same operation -
XORing input data with the keystream).

When ran without arguments it will print usage and exit:

    Usage: ./ofb_pipe [keyfile] [options]
    Options:
       -d   decrypt instead of encrypting

    When encrypting, first 16 bytes SENT is IV (generated randomly)
    When decrypting, first 16 bytes RECEIVED is IV

Keyfile has to be at least 16 bytes long, and first 16 bytes of the file
will be used as the key.

When encrypting a file example usage may look like this (assuming
keyfile.secret contains the key):

    $ cat infile | ./ofb_pipe keyfile.secret > outfile
    $ ./ofb_pipe keyfile.secret < infile > outfile

To decrypt data swap infile and outfile around and add -d as the third
argument.

Input and output could also be network sockets when piped from/to netcat
or other similar commands. Example commands used to send input from one
terminal to the output of another terminal, potentially on another
machine, through an encrypted TCP tunnel could look like this:

    # receiving (listening)
    $ nc -l [address] -p [port] | ./ofb_pipe keyfile.secret -d | cat
    # sending (connecting)
    $ cat | ./ofb_pipe keyfile.secret | nc [address] [port]

Both parties must obviously use the same preshared keyfile.secret.

It's important to note that, while the program works on a stream of
bytes instead of blocks and may be used to encrypt streams such as
sockets, it is still important to not divide encrypted output from it
into parts, because first 16 bytes written to output when encrypting and
first 16 bytes read from input when decrypting is treated as the IV.
