//Library for I/O and Memory Routine
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//Header File
#include "gtopoRead.h"
//Main Function
int main(int argc, char **argv)
{
	// Check if correct number of arguments were provided
	//If the argument is 1
	if (argc == 1)
		{
			// If no arguments given, print error message
			printf("Usage: ./gtopoEcho inputFile width height outputFile");
			// Return appropriate error code
			return 0;
		}
	//Wrong Number of Arguments
	if (argc != 5)
	{
		// wrong arg count 
		// print an error message       
		printf("ERROR: Bad Argument Count\n");
		// and return an error code    
		return EXIT_WRONG_ARG_COUNT;
	}
	//define struct to store values of the first input file
	FileInfo *fileValues1 = initialisationOfReadFileStruct();
	//define struct to store values of the second input file
    FileInfo *fileValues2 = initialisationOfReadFileStruct();

	// Open the input file
	FILE *inputFile1 = fopen(argv[1], "rb");

	//Calls the read function to validate the input file
	checkread(inputFile1,argv[1]);
	//Checks the width of the file
	checkWidth(inputFile1,argv[1],fileValues1,argv[2]);
	//Checks the Height of the file
	checkHeight(inputFile1,argv[1],fileValues1,argv[3]);
	//Reads the Image Data
	readImageDataBinary(fileValues1,inputFile1, argv[1]);

	// Open the second input file
    FILE *inputFile2 = fopen(argv[4], "rb");
	//Calls the read function to validate the second input file
	checkread(inputFile2,argv[4]);
	//Checks the width of the file
	checkWidth(inputFile2,argv[1],fileValues2,argv[2]);
	//Checks the Height of the file
	checkHeight(inputFile2,argv[1],fileValues2,argv[3]);
	//Reads the Image Data for second file
	readImageDataBinary(fileValues2,inputFile2, argv[4]);
	//Calls the compare function to compare two files

    compare(fileValues1,fileValues2);

	//All the things are done so close the file
    fclose(inputFile1);
	fclose(inputFile2);
	//Exit the program with no errors
	return EXIT_NO_ERRORS;
}