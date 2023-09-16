/**
These methods perform the bitwise arithmetic of adding, subtracting, and multiplying
the 8 bit Galois fields. 
*/

#ifndef _FIELD_H_
#define _FIELD_H_

/** Type used for our field, an unsigned byte. */
typedef unsigned char byte;

/** Number of bits in a byte. */
#define BBITS 8

/*
//This function performs the addition operation in the 8-bit Galois field used by 
//AES. It adds a and b and returns the result.
@param a first field to add
@param b second field to add
@return the sum of the fields (bitwise, exclusive or)
*/
byte fieldAdd( byte a, byte b );

/*
//This function performs the subtraction operation in the 8-bit Galois field used
//by AES. It subtracts b from a and returns the result.
@param a first field (subtracted from)
@param b second field (subtracted, doesn't matter though bc it's complementary.)
@return the difference of the fields (bitwise, exclusive or)
*/
byte fieldSub( byte a, byte b );

/*
This function performs the multiplication operation in the 8-bit Galois field used by AES. 
It multiplies a and b and returns the result.
@param first field in the operation
@param second field in the operation
@return the product of the fields 
*/
byte fieldMul( byte a, byte b );

#endif
