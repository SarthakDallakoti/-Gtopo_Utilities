#include <stdlib.h>
#include <stdio.h>
#include "FileInfo.h"
// Error code to be used when returing an error code or successul execution code
#define EXIT_NO_ERRORS 0
#define EXIT_WRONG_ARG_COUNT 1
#define EXIT_BAD_INPUT_FILE 2
#define EXIT_BAD_COMMENT_LINE 4
#define EXIT_BAD_IMAGE_MALLOC_FAILED 7
#define EXIT_BAD_DATA 8
#define EXIT_OUTPUT_FAILED 9
#define EXIT_MISCELLANEOUS 100

#define MAX_COMMENT_LINE_LENGTH 130

FileInfo *initialisationOfReadFileStruct();
int checkHeight(FILE* inputFile,char* filename,FileInfo *fileValues,char* height);
int checkWidth(FILE* inputFile,char* filename,FileInfo *fileValues,char* width);
int checkread(FILE* inputFile,char* filename);
int checkwrite(FILE* inputFile,char* filename,FileInfo *fileValues);
int readCommentAndCheck(FILE *file, int maxCommentLen, FileInfo *fileValues,char* filename);
int readImageDataBinary(struct FileInfo *fileValues,FILE *inputFile, char* filename);
int writeFile(FILE*outputFile,char *filename,FileInfo *fileValues);
int compare(FileInfo *fileValues1,FileInfo *fileValues2);
int Reduce(FileInfo *fileValues1,FileInfo *fileValues2, int reductionFactor);