/**
*/

#include "field.h"
#include <stdlib.h>
#include <stdio.h>
#define MAXIDX 7

byte fieldAdd( byte a, byte b )
//This function performs the addition operation in the 8-bit Galois field used by 
//AES. It adds a and b and returns the result.
{
    return a^b;
}

byte fieldSub( byte a, byte b )
//This function performs the subtraction operation in the 8-bit Galois field used
//by AES. It subtracts b from a and returns the result.
{
    return a^b;
}

byte fieldMul( byte a, byte b )
//This function performs the multiplication operation in the 8-bit Galois field 
//used by AES. It multiplies a and b and returns the result.
{   
    // a running sum of xOr operations
    unsigned int xOrResult = 0; 
    // a copy of arg a that will be shifted as needed
    unsigned int multA; 

    // if the first bit of b is a 1 and not a 0...
    if ((0x01 & b) == 1) {
        // set xOrResult to be a
        xOrResult = a;
    }

    //shift a left one place
    multA = a << 1;
    //shift value b right one place (a different bit is now in the smallest place)
    b = b >> 1;

    //multiplying via xOr operation
    for (int i = 0; i < MAXIDX; i++) {
        // if the first bit of b is a 1 and not a 0...
        if ((0x01 & b) == 1) {
            // set xOrResult to be the xOr of itself and multA ( a running total )
            xOrResult = xOrResult ^ multA;
        }
        //shift multA left 1 place
        multA = multA << 1;
        //shift b right 1 place (a different bit is now in the smallest place)
        b = b >> 1;
    }

    int hiOrdOneIdx = 0;
    unsigned int copyOfResult = xOrResult;
    //loop through size of int (32 bits) to find highest order 1
    for (int i = 0; i < sizeof(int) * 8; i++) {
        // if the result, shifted over i places then masked off to the smallest bit, equals 1
        if ((copyOfResult >> i) & 1) {
            // then the new highest order is i
            hiOrdOneIdx = i;
        }
    }

    //using the highest order 1 index, trim off overflow 
    int reducer;
    // if there is a 1 in any index higher than the max index
    while (hiOrdOneIdx > MAXIDX) {
        //use the reducer and shift it left by highest index - max spaces
        reducer = 0x11B << (hiOrdOneIdx - (MAXIDX + 1));
        //set xOrResult to the xOr of itself and the shifted reducer
        xOrResult ^= reducer;
        //continue reducing xOrResult (until size of 32 bits is reached)
        //find the next highest index of a 1
        hiOrdOneIdx = 0;
        for (int i = 0; i < sizeof(int)*8; i++) {
            if ((xOrResult >> i) & 1) {
                hiOrdOneIdx = i;
            }
        }
    }

    return xOrResult;

    // byte movingMask = 0x01;

    // // to help with reducing
    // int lengthOfResult;

    // //use mask to see where the ones are in b
    // for (int i = 0; i < MAXIDX; i++) {

    //     if (( newTimes >> i) & 0x01) {
    //         xOrResult = i
    //     }
    //     //if the '&' of b and this moving mask has a 1 in it instead of all 0s
    //     // ('&' means both inputs have a 1 in that spot)
    //     if ((b & (movingMask << i)) != 0) {
    //         //once we finish multiplication the max length of xOrResult will be:
    //         lengthOfResult = i + MAXIDX;

    //         xOrResult = multA ^ ( multB << i);
    //     }
    // }
    // printf("xOrResult: %d\n", xOrResult);
    // printf("maxLength: %d\n", lengthOfResult);

    // int reducer = 0x11B;
    // movingMask = 0x01;

    // //reduction back down to 8 bits
    // for (int i = lengthOfResult - 1; i > 7; i--) {
    //     if ((xOrResult & (movingMask << (i - 8))) != 0) {
    //         xOrResult =  ( reducer << i - 8 ) ^ xOrResult;
    //     }
    // }

    // printf("xOResult: %d\n", xOrResult);

    // return xOrResult;
}
