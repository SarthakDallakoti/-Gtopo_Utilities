#ifndef _FILEINFO_
#define _FILEINFO_

typedef struct FileInfo {
  char *commentLine;
  unsigned int width;
  unsigned int height;
  unsigned char **imageData;
} FileInfo;

#endif
