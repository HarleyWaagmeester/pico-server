/**
 * Feel free to use this example code in any way
 * you see fit (Public Domain)

 * Part of a very simple webserver using the picohttpd codebase.


 * Within a string, search for a string and replace it with another string.


 * searchReplace ("string to be modified", "search string", "replacement string"")


 * Use of this with huge strings is not tested.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SOURCE_SIZE (0x100000)

char * searchReplace(char * string, char *toRep, char *rep){
  int i = 0;
  int index = 0;
  char *locOfToRep;
  //  int lenToRep,lenStr,lenAfterLocRep;
  static char buf[MAX_SOURCE_SIZE];
  static char* buffer;
  buffer = calloc(MAX_SOURCE_SIZE,1);
  while ((locOfToRep = strstr(string,toRep))){
    memcpy(buf,string,locOfToRep-string);
    buf[locOfToRep-string] = 0;
    strcat(buffer,buf);
    i++;
    //printf("%d\n",i);
    while(0){};
    index = strlen(toRep)+locOfToRep-string; 
    strcat(buffer,rep);
    //      printf("%s\n",string);
    // strcat(buffer,string+index);
    string += index;
    //printf("buf= %s\nbuffer= %s\nindex=%d\nstring= %s\n ",buf,buffer,index,string);
  }
  strcat(buffer,string);
  return buffer;
}


/* int main(){ */
/*     char * string = "#id1 {color: blue;border: solid;}"; */
/*     char* result; */
/*     result = searchReplace(string, "{", "{\n"); */
/*     result = searchReplace(result, "}", "}\n"); */
/*     result = searchReplace(result, ";", ";\n"); */

/*     printf("%s\n",result); */
/* } */
