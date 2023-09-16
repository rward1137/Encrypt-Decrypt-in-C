/**
Functions that perform the encryption and decryption steps
*/

#ifndef _AES_H_
#define _AES_H_

#include "field.h"

/** Number of bytes in an AES key or an AES block. */
#define BLOCK_SIZE 16

/** Numer of rows when a data block is arranged in a square. */
#define BLOCK_ROWS 4

/** Numer of columns when a data block is arranged in a square. */
#define BLOCK_COLS 4

/** Number of bytes in a word. */
#define WORD_SIZE 4

/** Number of roudns for 128-bit AES. */
#define ROUNDS 10



/*
This function computes the g function used in generating the subkeys from the 
original, 16-byte key. It takes a 4-byte input via the src parameter and returns 
a 4-byte result via the dest parameter. The value, r, gives the round number, 
between 1 and 10 (inclusive).
@param dest the destination array
@param src the source array
@param r round number
*/
void gFunction( byte dest[ WORD_SIZE ], byte const src[ WORD_SIZE ], int r );

/*
This function fills in the subkey array with subkeys for each round of AES, computed
from the given key.
@param subkey 2d byte array that holds all the subkeys for encryption steps
@param key the provided original key
*/
void generateSubkeys( byte subkey[ ROUNDS + 1 ][ BLOCK_SIZE ], byte const key[ BLOCK_SIZE ] );

/*
This function performs the addSubkey operation, adding the given subkey (key) to the 
given data array.
@param data the destination
@param the key to be added
*/
void addSubkey( byte data[ BLOCK_SIZE ], byte const key[ BLOCK_SIZE ] );

/*
This function rearranges a block of 16 data values from the one-dimensional 
arrangement to the 4 × 4 arrangement.
@param square the 2d representation of the given data block
@param data the given data block
*/
void blockToSquare( byte square[ BLOCK_ROWS ][ BLOCK_COLS ], byte const data[ BLOCK_SIZE ] );

/*
This function rearranges a 4 × 4 arrangement of data values, returning them as a 
one-dimensional array of 16 values.
@param data the regular representation of the given square
@param the given square
*/
void squareToBlock( byte data[ BLOCK_SIZE ], byte const square[ BLOCK_ROWS ][ BLOCK_COLS ] );

/*
This function performs the shiftRows operation on the given 4 × 4 square of values.
@param square to have its rows shifted
*/
void shiftRows( byte square[ BLOCK_ROWS ][ BLOCK_COLS ] );

/*
This function performs the inverse shiftRows operation on the given 4 × 4 square of values.
@param square to have its rows unshifted
*/
void unShiftRows( byte square[ BLOCK_ROWS ][ BLOCK_COLS ] );


/*
This function performs the mixColumns operation on the given 4 × 4 square of 
values, multiplying each column by the matrix shown in the requirements section.
@param square to have its columns mixed
*/
void mixColumns( byte square[ BLOCK_ROWS ][ BLOCK_COLS ] );


/*
This function performs the inverse of the mixColumns operation on the given 4 × 4 
square of values, multiplying each column by the inverse of the mixColumns matrix 
shown in the requirements section.
@param square to have its columns unmixed
*/
void unMixColumns( byte square[ BLOCK_ROWS ][ BLOCK_COLS ] );

/*
This function encrypts a 16-byte block of data using the given key. It generates the
11 subkeys from key, adds the first subkey, then performs the 10 rounds of operations
needed to encrypt the block.
@param data to be encrypted
@param key to use for encryption
*/
void encryptBlock( byte data[ BLOCK_SIZE ], byte key[ BLOCK_SIZE ] );

/*
This function decrypts a 16-byte block of data using the given key. It generates the 
11 subkeys from key, then performs the 10 rounds of inverse operations (and then an 
addSubkey) to decrypt the block.
@param data to be decrypted
@param key to use for decryption
*/
void decryptBlock( byte data[ BLOCK_SIZE ], byte key[ BLOCK_SIZE ] );


#endif
