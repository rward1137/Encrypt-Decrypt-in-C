#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "io.h"
#include "field.h"

//This function reads the contents of the binary file with the given name. It returns 
//a pointer to a dynamically allocated array of bytes containing the entire file 
//contents. The size parameter is an integer that’s passed by reference to the function. 
//The function fills in this integer with the total size of the file (i.e., how many bytes 
//are in the returned array).
byte *readBinaryFile( char const *filename, int *size )
{
  FILE *src = fopen(filename, "rb");

  //error message if file not found
  if (src == NULL) {
    fprintf(stderr, "Can't open file: %s\n", filename);
    exit(INVALID);
  }
  int length = 0;
  int capacity = BLOCK_SIZE;

  // start with 16 bytes
  byte *data = (byte *) malloc(capacity * sizeof(byte));

  while ( (length = fread( &data[*size], sizeof(byte), BLOCK_SIZE, src )) != 0) {
    *size += length;
    if ( *size >= capacity ) {
      //realloc to an array double the size and keep reading
      capacity *= DOUBLE;
      byte *temp = (byte *) realloc(data, capacity * sizeof(byte));
      data = temp;
    }
  }
    fclose(src);
    return data;
}

//This function writes the contents of the given data array (in binary) to the file 
//with the given name. The size parameter says how many bytes are contained in the 
//data array.
void writeBinaryFile( char const *filename, byte *data, int size )
{
  FILE *dest = fopen(filename, "wb");

  //error message if file not found
  if (dest == NULL) {
    fprintf(stderr, "Can't open file: %s\n", filename);
    exit(INVALID);
  }

  fwrite(data, sizeof(byte), size, dest);

  fclose(dest);
}
