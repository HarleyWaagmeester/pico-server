#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>

#include "../headers/httpd.h"

#define READER 0
#define WRITER 1
#define MAX_TEXT_SIZE 8096
#define R200  printf("HTTP/1.1 200 OK\r\n\r\n");

//prototypes
int piper();
char * searchReplace(char * string, char *toRep, char *rep);
int do_html();

int main(int c, char** v)
{
  serve_forever("12913");
  return 0;
}

void route()
{
  ROUTE_START()

    ROUTE_GET("/")
    {
      R200
        printf("Hello! You are using %s", request_header("User-Agent"));
    }

  ROUTE_POST("/")
    {
      R200
        printf("Wow, seems that you POSTed %d bytes. \r\n", payload_size);
      printf("Fetch the data using `payload` variable.");
    }
  
  ROUTE_GET("/ping")
    {
      R200
        piper("ping");
    }

  ROUTE_GET("/netstat")
    {
      R200
        piper("netstat");
    }

  ROUTE_GET("/ping-local")
    {
      R200
        piper("ping-local");
    }

  ROUTE_END()
    }

int
piper(char* module)
{
  FILE* fpipe;
  char buf[MAX_TEXT_SIZE];
  char command[1024];

  command[0] = 0;

  if (0 == strcmp("ping", module)) {
    strcpy(command, "ping 10.0.1.1");
  }
  if (0 == strcmp("ping-local", module)) {
    strcpy(command, "ping hal");
  }
  if (0 == strcmp("netstat", module)) {
    strcpy(command, "netstat -ctn");
  }
  
  if (command[0] == 0) {
    return 1;
  }

  do_html();

  if ( !(fpipe = (FILE*)popen(command,"r")) )
    {  // If fpipe is NULL
      syslog(LOG_CRIT,"%s","Problem with pipe");
      exit(1);
    }

  while (NULL != fgets(buf, MAX_TEXT_SIZE, fpipe)) {
    printf("%s",buf);
    }

  pclose(fpipe);
  _exit(EXIT_SUCCESS);

}

int
do_html() {
  //  printf("HTTP/1.1 200 OK\r\n\r\n");
  printf("<html><head><meta http-equiv=\"Content-type\" content=\"text/html;charset=UTF-8\">");
  printf( "<title>SYSS</title>");
  printf( "<meta name=\"description\" content=\"UTILS\">");
  printf( "<meta name=\"keywords\" content=\"UTILS\">");
  printf( "<meta http-equiv=\"Content-type\" content=\"text/html;charset=UTF-8\">");
  //  printf( "<meta name=\"\"ROBOTS\" content=\"noindex\">");
  printf("<script type='text/javascript' src='http://localhost:8080/js/server.js'></script>");
  //    printf( "<link rel='stylesheet' type='text/css' href='/exec/css/link_button.css'>"
  printf("</head><body>");

  // Don't close the textarea element so that stdout will go into the textarea.
  printf("<textarea id='t1' spellcheck='false' readonly tabindex='0' style='height:%s;width:%s'>","100%","100%");
  return 0;
}

/* function scrollToBottom(id){ */
/*   var div = document.getElementById(id); */
/*   div.scrollTop = div.scrollHeight - div.clientHeight; */
/* }     */

/////////////////////////////////////////////////////
// Save this code.
////////////////////////////////////////////////////

/* int */
/* piper(char* module) */
/* { */
/*   FILE* fpipe; */
/*   int pipefd[2]; */
/*   pid_t cpid; */
/*   char buf[MAX_TEXT_SIZE]; */
/*   char rbuf[MAX_TEXT_SIZE]; */
/*   char command[1024]; */

/*   if (pipe(pipefd) == -1) { */
/*     perror("pipe"); */
/*     exit(EXIT_FAILURE); */
/*   } */

/*   command[0] = 0; */

/*   if (0 == strcmp("ping", module)) { */
/*     strcpy(command, "ping 10.0.1.1"); */
/*   } */
/*   if (0 == strcmp("ping-local", module)) { */
/*     strcpy(command, "ping hal"); */
/*   } */
/*   if (0 == strcmp("netstat", module)) { */
/*     strcpy(command, "netstat -ctn"); */
/*   } */
  
/*   if (command[0] == 0) { */
/*     return 1; */
/*   } */

    
/*   cpid = fork(); */
/*   if (cpid == -1) { */
/*     perror("fork"); */
/*     exit(EXIT_FAILURE); */
/*   } */

/*   if (cpid == 0) {    /\* Child writes from pipe *\/ */
/*     close(0); */
/*     close(1); */
/*     close(2); */
/*     close(pipefd[READER]);          /\* Close unused read end *\/ */

/*     if ( !(fpipe = (FILE*)popen(command,"r")) ) */
/*       //        if ( !(fpipe = (FILE*)popen("netstat -ctn","r")) ) */
/*       {  // If fpipe is NULL */
/*         syslog(LOG_CRIT,"%s","Problem with pipe"); */
/*         //        perror("Problems with pipe"); */
/*         exit(1); */
/*       } */

/*     while (NULL != fgets(buf, MAX_TEXT_SIZE, fpipe)) { */
/*       // Be sure to write the '\0', hence the '+1' */
/*       write(pipefd[WRITER], &buf, strlen(buf)+1); */
/*       usleep(100000); // Give the parent enough time to read the pipe, else the buffer will be overwritten, a FIFO might be better here. */
/*       //            fprintf(stderr,"in pipe loop %s\n",buf); */
/*     } */

/*     pclose(fpipe); */
/*     close(pipefd[WRITER]);          /\* Reader will see EOF *\/ */
/*     _exit(EXIT_SUCCESS); */

/*   } else {            /\* Parent reads from pipe *\/ */
/*     close(pipefd[WRITER]);          /\* Close unused write end *\/ */
/*     do_html(); */
/*     /\* int i = 0; *\/ */
/*     while (0!= read(pipefd[0], rbuf, 1024)) { */
/*       rbuf[1023] = 0; */
/*       printf("%s",rbuf); */
/*     } */
/*     /\* while (NULL != fgets(rbuf, 1024, readpipe)) { *\/ */
/*     /\*   printf("%s",rbuf); *\/ */
/*     /\*   //      usleep(500); *\/ */
/*     /\*   fprintf(stderr, "in fgets loop\n"); *\/ */
/*     /\* } *\/ */
/*     printf("exiting...\n"); */
/*     wait(NULL);                /\* Wait for child *\/ */
/*     exit(EXIT_SUCCESS); */
/*   } */
/* } */
