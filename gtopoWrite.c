//Library for I/O and Memory Routine
#include <stdlib.h>
#include <stdio.h>
//Header File Used for this Program
#include "gtopoRead.h"

int writeFile(FILE*outputFile,char *filename, struct FileInfo *fileValues){
  //First loop to read the height
  for(int k = 0; k < fileValues -> height ; k++)
  {
    //Second loop to read the width
	  for(int l = 0; l < fileValues -> width ; l++)
    {
      //Writes the data in 2D array
     fwrite(&fileValues->imageData[k][l],sizeof(unsigned char),1,outputFile);
    }
  }
  // at this point, we are done and can exit with a success code 
  return EXIT_NO_ERRORS;
}
