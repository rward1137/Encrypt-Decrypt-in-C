
#include "field.h"

/** Number of bytes in an AES key or an AES block. */
#define BLOCK_SIZE 16

#define DOUBLE 2

#define INVALID 1
/*
//This function reads the contents of the binary file with the given name. It returns 
//a pointer to a dynamically allocated array of bytes containing the entire file 
//contents. The size parameter is an integer that’s passed by reference to the function. 
//The function fills in this integer with the total size of the file (i.e., how many bytes 
//are in the returned array).
@param filename the path to the file
@param size the address to use for storing the number of bytes
@return byte * the data read in
*/
byte *readBinaryFile( char const *filename, int *size );

/*
//This function writes the contents of the given data array (in binary) to the file 
//with the given name. The size parameter says how many bytes are contained in the 
//data array.
@param filename the path to the file
@param data the data to be written
@param size the number of bytes to be written
*/
void writeBinaryFile( char const *filename, byte *data, int size );

