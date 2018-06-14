
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <malloc.h>

#include "subdirs.h" 
/**
this is an example of the type of directory tree we are supporting
/  
   1
   2
   3/ 
      4
      5
      6/
         7
the files in the dirent are 
/1
/2
/3 
/3/4
/3/5
/3/6
/3/6/7

*/

/**
@function getdir
@return returns the name of the directory in which a file exists
*/
char *get_dir(const char *filename) {
  int i;
  int filelen = strlen(filename);
  
  for(i = filelen-1; i>=0; i--) {
    if(filename[i] == '/') {
      char *dir = malloc(i+1);
      strncpy(dir, filename, i);
      dir[i] = '\0';
      fprintf(stderr, "In get_dir: i = %d\n", i);
      return dir;
    }
  }

  return 0;
}

/**
@function isfilein
@about This function is used to find if the filename is present in dir
Filename is of the format /a/b/c/d and directory may be /a/b/ 
There is no trailing slash in the directory name, or this function does not
expect any.

This function expects that the root directory is called "/"
*/
int isfilein( const char *filename, const char *dir) {
  assert(filename && dir);
  
  int dirlen = strlen(dir);  
  int filelen = strlen(filename);
  if( filelen < (dirlen+1) )// filename should be at least one byte
    return 0;
 
  if(!strcmp(dir, "/")) {
     for (int i = 1; i < filelen; i++) {
       if(filename[i] == '/')
         return 0;
     }
     return 1;
  } else {
    if(!strncmp( filename, dir, dirlen)) {
      // check that there is a slash between dirname and actual filename 
      if( filename[dirlen] != '/')
         return 0;
      // check that there isnt any other slash in the filename
      int i;
      for (i = dirlen + 1; i < filelen; i++) {
        if(filename[i] == '/')
          return 0;
      }
      return 1;
    }
    return 0;
   }

  return 0;
}


