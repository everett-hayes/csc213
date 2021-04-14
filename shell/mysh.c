#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// This is the maximum number of arguments your shell should handle for one command
#define MAX_ARGS 128

int parseCommand(char* str);
int handleCommand(char* cmd, bool isBackGround);

int main(int argc, char** argv) {
  // If there was a command line option passed in, use that file instead of stdin
  if (argc == 2) {
    // Try to open the file
    int new_input = open(argv[1], O_RDONLY);
    if (new_input == -1) {
      fprintf(stderr, "Failed to open input file %s\n", argv[1]);
      exit(1);
    }

    // Now swap this file in and use it as stdin
    if (dup2(new_input, STDIN_FILENO) == -1) {
      fprintf(stderr, "Failed to set new file as input\n");
      exit(2);
    }
  }

  char* line = NULL;     // Pointer that will hold the line we read in
  size_t line_size = 0;  // The number of bytes available in line

  // Loop forever
  while (true) {

    // Print the shell prompt
    printf("$ ");

    // Get a line of stdin, storing the string pointer in line
    if (getline(&line, &line_size, stdin) == -1) {
      if (errno == EINVAL) {
        perror("Unable to read command line");
        exit(2);
      } else {
        // Must have been end of file (ctrl+D)
        printf("\nShutting down...\n");

        // Exit the infinite loop
        break;
      }
    }

    int exit = parseCommand(line);

    if (exit == 1) break;
  }

  // If we read in at least one line, free this space
  if (line != NULL) {
    free(line);
  }

  return 0;
}

int parseCommand(char* str) {

  char* current_position = str;

  while(true) {
    // Call strpbrk to find the next occurrence of a delimeter
    char* delim_position = strpbrk(current_position, "&;\n");

    if(delim_position == NULL) {

      return 0;

    } else {
      // There was a delimeter. First, save it.
      char delim = *delim_position;

      // Overwrite the delimeter with a null terminator so we can print just this fragment
      *delim_position = '\0';

      int res = 0;

      if (delim == '&') {
        res = handleCommand(current_position, true);
      } else {
        res = handleCommand(current_position, false);
      }

      if (res == 1) {
        return res;
      }

    }

    // Move our current position in the string to one character past the delimeter
    current_position = delim_position + 1;
  }

}

int handleCommand(char * cmd, bool isBackGround) {

  int waitResponse;

  int pidRes = waitpid(-1, &waitResponse, WNOHANG);

  while (pidRes > 0) {
    printf("[background process %d exited with status %d]\n", pidRes, waitResponse);
    pidRes = waitpid(-1, &waitResponse, WNOHANG);
  }

  char* args [MAX_ARGS + 1];
  int i = 0;
  
  char* saveptr;
  char* ptr = strtok_r(cmd, " \n", &saveptr);

  // split line into args 
  while (ptr != NULL) {
    args[i++] = ptr;
    ptr = strtok_r(NULL, " \n", &saveptr);
  }

  args[i] = NULL;

  if (args[0] == NULL) {
    return 0;
  } else if (strcmp(args[0], "cd") == 0) {
    chdir(args[1]);
    return 0;
  } else if (strcmp(args[0], "exit") == 0) {
    return 1;
  }

  int id = fork();

  if (id == 0) {
    int status = execvp(args[0], args);
    exit(status);
  } else if (!isBackGround) {
    wait(&waitResponse);
  } 

  if (!isBackGround) {
    printf("[%s exited with status %d]\n", args[0], waitResponse);
  }

  return 0;

}



























// int handleCommand(char* cmd) {

//   char* args [MAX_ARGS + 1];
//   int i = 0;
  
//   char* saveptr;
//   char* ptr = strtok_r(cmd, " \n", &saveptr);

//   // split line into args 
//   while (ptr != NULL) {
//     args[i++] = ptr;
//     ptr = strtok_r(NULL, " \n", &saveptr);
//   }

//   args[i] = NULL;

//   if (args[0] == NULL) {
//     return 0;
//   } else if (strcmp(args[0], "cd") == 0) {
//     chdir(args[1]);
//     return 0;
//   } else if (strcmp(args[0], "exit") == 0) {
//     return 1;
//   }

//   int childRes;

//   int wait_res = waitpid(-1, &childRes, WNOHANG);

//   while (wait_res > 0) {
//     printf("finished a child process");
//     wait_res = waitpid(-1, &childRes, WNOHANG);
//   }

//   int id = fork();

//   // check to see if we are a child process
//   if (id == 0) { 
//     int status = execvp(args[0], args);
//     exit(status);
//   } else {
//     wait(&childRes);
//   }

//   printf("[%s exited with status %d]\n", args[0], childRes);

//   return 0;
// }

// int handleBackgroundCommand(char* cmd) {

//   char* args [MAX_ARGS + 1];
//   int i = 0;
  
//   char* saveptr;
//   char* ptr = strtok_r(cmd, " \n", &saveptr);

//   // split line into args 
//   while (ptr != NULL) {
//     args[i++] = ptr;
//     ptr = strtok_r(NULL, " \n", &saveptr);
//   }

//   args[i] = NULL;

//   if (args[0] == NULL) {
//     return 0;
//   } else if (strcmp(args[0], "cd") == 0) {
//     chdir(args[1]);
//     return 0;
//   } else if (strcmp(args[0], "exit") == 0) {
//     return 1;
//   }
  
//   int id = fork();
//   int childRes;

//   if (id == 0) {
//     int status = execvp(args[0], args);
//     exit(status);
//   }


//   int wait_res = waitpid(-1, &childRes, WNOHANG);

//   /*
//   loop until wait_res is no longer going?
//   */
//   while (wait_res > 0) {
//     printf("finished a child process");
//     wait_res = waitpid(-1, &childRes, WNOHANG);
//   }


//   // if not & waitpid(id, &childRes, WNOHANG);
//   // if & waitpid(id, &childRes, WNOHANG);



//   // int id2 = fork();

//   // if (id2 == 0) {
//   //   while (waitpid(id, &childRes, WNOHANG) <= 0) {}
//   //   printf("child process has finished\n");
//   //   exit(0);
//   // }

//   /*
//   keep going on
//   once waitpit returns > 0 we know the child is done
//   */

//   // int temp = getpid();
//   // printf("temp was %d before the fork\n", temp);

//   // int id2 = fork();

//   // printf("my id is %d after the fork'n", id2);

//   // if (id2 == 0) {
//   //   while (waitpid(temp, &childRes, WNOHANG) <= 0) {}
//   //   printf("child process has finished\n");
//   //   exit(0);
//   // }
  

//   // // where are we looping on waitpid???

//   // while (waitpid(id, &childRes, WNOHANG) <= 0) { 
//   //   /* when there is no more child process exists then it terminate */ 
//   // }
//   // printf("child process has finished\n");

//   // //int return_pid = waitpid(id, &childRes, WNOHANG);

//   // printf("done\n");

//   // if (return_pid == -1) {
//   //   printf("something bad has happened\n");
//   // } else if (return_pid == 0) {
//   //   printf("the child is still running\n");
//   // } else if (return_pid == id) {
//   //   printf("the child is finished\n");
//   // }

//   return 0;
// }
