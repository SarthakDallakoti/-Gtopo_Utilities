//Library for I/O and Memory Routine
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
//Header File Used for this Program
#include "gtopoRead.h"

FileInfo *initialisationOfReadFileStruct (){
  // Creates and initialises the fileInfo structure to default values
  FileInfo *output = (FileInfo*) malloc (sizeof(FileInfo));
  output->commentLine = NULL;
  output->width=0;
  output->height=0;
  output->imageData=NULL;
  // Return the pointer to this structure
  return output;
}

int checkHeight(FILE* inputFile,char* filename,FileInfo * fileValues,char* height){
  int i = 0;
  //stores length of string
  int len = strlen(height);
  for (i = 0; i < len ; i++)
  {
    //if (number[i] > '9' || number[i] < '0')
    if (!isdigit(height[i])){
      //the character in height is non Numeric
      //print error message
      fclose(inputFile);
      printf("ERROR: Bad Dimensions (%s)",filename);
      //return appropriate error code
      exit(5);
    }
  }
  //assign height pointer to integer value of height
  fileValues->height = atoi(height);
  //sucessfully stored height
  //return success code
  return EXIT_NO_ERRORS;
}

//checks the width passed in commandline
int checkWidth(FILE* inputFile,char* filename,FileInfo * fileValues,char* width){
  int i = 0;
  //stores length of string
  int len = strlen(width);
  for (i = 0; i < len ; i++)
  {
    //if (number[i] > '9' || number[i] < '0')
    if (!isdigit(width[i])){
      //the character in width is non Numeric
      //print error message
      fclose(inputFile);
      //print error message
      printf("ERROR: Bad Dimensions (%s)",filename);
      //return appropriate error code
      exit(5);
    }
  }
  //assign width pointer to integer value of width
  fileValues->width = atoi(width);
  //succesfully stored width
  //return sucess message
  return EXIT_NO_ERRORS;
}
int checkread(FILE* inputFile,char* filename){
  if (inputFile == NULL)
  {
    //the first file is not readable
    //print error statemnt
    printf("ERROR: Bad File Name (%s)\n", filename);
    //exit the program with the correct error code
    exit(2);
   }
   return 0;
 }

//checks if the file is writeable
//takes file pointer and filename as parameters
int checkwrite(FILE* inputFile,char* filename,FileInfo *fileValues){
  if (inputFile == NULL)
  {
    //free memory
    free(fileValues-> imageData);
    //print appropriate error meassage
    printf("ERROR: Output Failed (%s)\n", filename);
    //return error code
    exit(9);
  }
  //the file is writeable
  //return sucess code
  return 0;
}
int readCommentAndCheck(FILE *file, int maxCommentLen,FileInfo *fileValues,char* filename)
{
  //Scans the whitespace
  fscanf(file," ");
  char nextChar = fgetc(file);
  //Initialize comment length
  int commentlength = 0;
  // Check if this is a comment line
  if (nextChar == '#')
  {
    fileValues->commentLine = (char *) malloc(maxCommentLen);
    // Capture the comment
    char *commentString = fgets(fileValues->commentLine, maxCommentLen, file);
    // Check if a comment was successfully read
    if (commentString == NULL)
    {
      //Free the comment line and exit the file
      free(fileValues->commentLine);
      fclose(file);
      exit (2);
    }
    //Length of the comment line
    commentlength = (int)strlen(commentString);
    //If comment line is greater than 128
    if (commentlength > 128){
      //Error message
      printf("ERROR: Bad Comment Line (%s)",filename);
      //Close the file and return the error code
      fclose(file);
      exit(EXIT_NO_ERRORS);
    }
    // correct comment
    free(fileValues->commentLine);
    return 1;
  }
  // Not a comment line
  else
  {
    ungetc(nextChar, file);
    //No error then return 0
    return EXIT_NO_ERRORS;
  }
}

int readImageDataBinary(FileInfo *fileValues,FILE *inputFile, char* filename)
{
  //allocate memory to store pixel data
	long nImagebytes = fileValues-> height * fileValues -> width * sizeof (unsigned char) * 2;
	fileValues->imageData = (unsigned char **) malloc(nImagebytes);

	  // Check if malloc function worked
	  if (fileValues->imageData == NULL)
	  {
			//malloc has failed
			//free memory
			//print error message
	    printf("ERROR: Image Malloc Failed");
			//free pointer
	    free(fileValues->imageData);
			//close the file
	    fclose(inputFile);
			//return exit code
	    exit(7);
	  }
		for (int k = 0; k < fileValues -> height ; k++){
			fileValues->imageData[k] = (unsigned char *) malloc(fileValues->width * sizeof(unsigned char));
			if (fileValues->imageData[k] == NULL)
			{
				// malloc failed 
				// free up memory
				free(fileValues->imageData);
				// close file pointer
				fclose(inputFile);
				// print an error message 
				printf("ERROR: Image Malloc Failed\n");
				// return error code 
				exit(EXIT_BAD_IMAGE_MALLOC_FAILED);
			}
		}
		//nested for loop to assign pixel data to 2d array
		for(int k = 0; k < fileValues -> height ; k++){
			for(int l = 0; l < fileValues -> width ; l++){
				//integer to store+
				 int lRead = fread(&fileValues->imageData[k][l], sizeof(unsigned char), 1, inputFile);
				 //printf("%zu\n",lRead );
				if (lRead == 0 ){
					//too little data
					//free memory
					free(fileValues->imageData);
					//close file pointer
					fclose(inputFile);
					//print error message
					printf("ERROR: Bad Data (%s)\n",filename);
					//return exit code
					exit(8);
				}
			}
		}
	// we're done with the file, so close it 
	fclose(inputFile);
	//exit with success code
}

int writeFile(FILE*outputFile,char *filename,FileInfo *fileValues){
  for(int k = 0; k < fileValues -> height ; k++){
	  for(int l = 0; l < fileValues -> width ; l++){
     fwrite(&fileValues->imageData[k][l],sizeof(unsigned char),1,outputFile);
    }
  }
  // at this point, we are done and can exit with a success code 
  return EXIT_NO_ERRORS;
}

int compare(FileInfo *fileValues1,FileInfo *fileValues2)
{
  if  (fileValues1->width != fileValues2->width || fileValues1->height != fileValues2->height){
			//conditions are not met and the files are distinct
			//print message
			printf("DIFFERENT");
			//return the code for successful comparison
			exit(0);
		}
		else{
			// the conditions are met and the files have identical structure
			//now to test if the pixel values are identical

			//create integer to count the number of identical pixels
			int identicalPixles = 0;

			//create integer to hold the product of dimensions
			long dimensions = fileValues1->width * fileValues1->height * sizeof(unsigned char);
			for(int i = 0; i < fileValues1 -> height ; i++){
				for(int j = 0; j < fileValues1 -> width ; j++){
					if (fileValues1->imageData[i][j] == fileValues2->imageData[i][j]){
						//the pixels are identical
						//add 1 to the variable
						identicalPixles++;
					}
				}
			}
    //If the dimension and values are same
    if (identicalPixles == dimensions){
      //They are identical
      printf("IDENTICAL");
      exit(EXIT_NO_ERRORS);
    }
    //If it is not equal
    else{
      printf("DIFFERENT");
      exit(EXIT_NO_ERRORS);
    }
  }
  return EXIT_NO_ERRORS;
}

int Reduce(FileInfo *fileValues1,FileInfo *fileValues2, int reductionFactor)
{
  fileValues2-> width =(fileValues1->width/reductionFactor);
  fileValues2-> height =(fileValues1->height/reductionFactor);

  //Allocatng memory
  fileValues2-> imageData =(unsigned char**) malloc(fileValues2->height * fileValues2->width * sizeof(unsigned char*));

  //If memory not allocated
  if(fileValues2 ->imageData == NULL){
    //Free memory
    free(fileValues1->imageData);
    //Print error message and exit the file
    printf("ERROR: Image Malloc Failed");
    exit(EXIT_BAD_IMAGE_MALLOC_FAILED);
  }

  for(int vertical =0; vertical< fileValues1->height;vertical++){
    fileValues2->imageData[vertical] =(unsigned char *) malloc(fileValues2->width * sizeof(unsigned char));

    //IF memory not allocated properly
    if(fileValues2->imageData[vertical] == NULL){
      //Free memory
      free(fileValues1->imageData);
      free(fileValues2->imageData);

      //Print error mesage and exit wih return code
      printf("ERROR: Image Malloc Failed");
      exit(EXIT_BAD_IMAGE_MALLOC_FAILED);
    }
  }
  //Save the data in new Image
  int newVertical =0 ;
  int newHorizontal =0;
  for(int vertical =0; vertical< fileValues1->height;vertical++){
    //if wertical is correct
    if((vertical% reductionFactor) ==0){
      for(int horizontal =0; horizontal< fileValues1->width;horizontal++){
        //if pixels are correct
        if((horizontal%reductionFactor)==0){
          //Copy pixel into new structure
          fileValues2->imageData[newVertical][newHorizontal] = fileValues1 ->imageData[vertical][horizontal];

          //Move to next pixel
          newHorizontal++;
        }
      }
      //Move to new row
      newVertical++;
      newHorizontal =0;
    }
  }
  //free(fileValues1->imageData);
  return EXIT_NO_ERRORS;
}
