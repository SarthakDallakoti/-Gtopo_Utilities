//Library for I/O and Memory Routine
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//Header File Used in the program
#include "gtopoRead.h"

//Main Function
int main(int argc, char **argv)
{
  int codemagic;
  if (argc == 1)
  {
    //Condition if only 1 argument is provided
		printf("Usage: ./gtopoReduce input width height reduction_factor output");
		return EXIT_NO_ERRORS;
	}
  if (argc == 2 || argc == 3)
  {
    //If there is bad argument count
    printf("ERROR: Bad Argument Count");
		return EXIT_WRONG_ARG_COUNT;
  }
  //To convert reduction Factor into integer
  char scaling_factor [40];
  strcpy(scaling_factor,argv[4]);
  int z = atoi (scaling_factor);
  if (z < 0)
  {
    //Checking if it is a negative sacling factor
    //Exit with error message and return code
    printf("ERROR: Miscellaneous (Negative Scaling Factor)");
    return EXIT_MISCELLANEOUS;
  }
  for (int i =0; scaling_factor[i]!= '\0'; i++)
  {
    //Checking if it is a non numeric value
    if (isdigit(scaling_factor[i]) == 0)
    {
      //Exit with error message and return code
      printf("ERROR: Miscellaneous (Non-Numeric Value)");
      return EXIT_MISCELLANEOUS;
    }
  }
    
  //Checking for bad argument count
	if (argc != 6)
  {
    //Exit with error message and return code
		printf("ERROR: Bad Argument Count");
		return EXIT_WRONG_ARG_COUNT;
	}
  int codeRead;
  //define struct to store values of the first input file
	FileInfo *fileValues1 = initialisationOfReadFileStruct();
  //define struct to store values of the second input file
  FileInfo *fileValues2 = initialisationOfReadFileStruct();

  //Open the first input file
	FILE *inputFile = fopen(argv[1], "r");
	// Read to file and check whether it has read successfully
  checkread(inputFile,argv[1]);
  //Checks the width of the file
  checkWidth(inputFile,argv[1],fileValues1,argv[2]);
  //Checks the height of the file
	checkHeight(inputFile,argv[1],fileValues1,argv[3]);
  //Reads the Image Data
	readImageDataBinary(fileValues1,inputFile, argv[1]);

  //Call the reduce function to reduce the file size
  Reduce(fileValues1,fileValues2,z);
  // Open output file
  FILE *outputFile = fopen(argv[5], "w");
	// Write to file the content of input file
	if (outputFile == NULL)
	{
		// Terminate with error code
		free(fileValues1->imageData);
		printf("ERROR: Output Failed (%s)",argv[5]);
		exit (9);
  }
  //Write the reduced file using second file pointer
	writeFile(outputFile,argv[5],fileValues2);
	// Check if it has written successfully
    //fclose(inputFile);
	fclose(outputFile);
	printf("REDUCED");
  //Return no errors
	return EXIT_NO_ERRORS;
}
