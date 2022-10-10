//Library for I/O and Memory Routine
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//Header File Used in the program
#include "gtopoRead.h"

int main(int argc, char **argv)
{
	// Check if correct number of arguments were provided
	if (argc == 1)
	{
		// If no arguments given, print error message
		printf("Usage: ./gtopoEcho inputFile width height outputFile");
		// Return appropriate error code
		return 0;
	}
	if (argc != 5)
	{ 
		// wrong arg count 
		// print an error message        
		printf("ERROR: Bad Argument Count\n");
		// and return an error code      
		return EXIT_WRONG_ARG_COUNT;
	}
	//define struct to store values of the input file
	FileInfo *fileValues = initialisationOfReadFileStruct();
	// Open the input file
	FILE *inputFile = fopen(argv[1], "rb");
	//Calls the read function to validate the input file
	checkread(inputFile,argv[1]);
	//Checks the width of the file
	checkWidth(inputFile,argv[1],fileValues,argv[2]);
	//Checks the height of the file
	checkHeight(inputFile,argv[1],fileValues,argv[3]);
	//Reads the Image Data
	readImageDataBinary(fileValues,inputFile, argv[1]);

	// Open output file
	FILE *outputFile = fopen(argv[4], "w+");
	//Check if outpul fill is null
	if (outputFile == NULL)
	{
		// Terminate with error code
		free(fileValues->imageData);
		printf("ERROR: Output Failed (%s)",argv[4]);
		exit (9);
  }
	//After Sanity check write to the output file
	writeFile(outputFile, argv[4], fileValues);
	//Close the outtput file
	fclose(outputFile);
	//Success Message
	printf("ECHOED");
	//Exit with no Errors
	return EXIT_NO_ERRORS;
}
