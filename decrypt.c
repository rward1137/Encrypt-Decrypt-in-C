#include "io.h"
#include "aes.h"
#include "field.h"
#include <stdlib.h>
#include <stdio.h>
/*
Accepts a key file path, a data file path, and an output file path for decryption of data
@param argc the number of arguments 
@param argv the array of arguments
@return int the exit status
*/
int main(int argc, char**argv) {

    //check that required args are included
    if (argc < 4) {
        fprintf(stderr, "usage: decrypt <key-file> <input-file> <output-file>\n");
        exit(INVALID);
    }

    //read the key file input
    int sizeK = 0;
    byte *key = readBinaryFile(argv[1], &sizeK);

    //must be 16 bytes
    if (sizeK != BLOCK_SIZE) {
        fprintf(stderr, "Bad key file: %s\n", argv[1]);
        exit(INVALID);
    }
    int sizeD = 0;
    byte *data = readBinaryFile(argv[2], &sizeD);

    if (sizeD % BLOCK_SIZE != 0) {
        fprintf(stderr, "Bad ciphertext file length: %s\n", argv[2]);
        exit(INVALID);
    }

    int marker = 0;
    int numBlocks = sizeD / BLOCK_SIZE;

    while (numBlocks > 0) {
        decryptBlock(data + marker, key);
        marker += BLOCK_SIZE;
        numBlocks--;
    }

    writeBinaryFile(argv[3], data, sizeD);

    free(key);
    free(data);


    return 0;
}
