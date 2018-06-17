/**
 * @breif Linux inter process communication using pipes.
 * @author Juan Manuel Gomez <greenlean@protonmail.com>
 * @copyrigth 
 */


#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
  int pipefd[2];
  pid_t cpid;
  char read_buf[80];

  if (argc != 2) {
    cerr << "Usage: %s <strig>\n" << argv[0];

    exit(EXIT_FAILURE);
  }

  if (pipe(pipefd) == -1) {
    cerr << "Error opening pipe" << endl;
    exit(EXIT_FAILURE);
  }

  //Create two process
  cpid = fork();
  if (cpid == -1) {
    cerr << "fork Error creating child process" << endl;
    exit(EXIT_FAILURE);
  }

  if (cpid == 0) {    /* Child reads from pipe */
    close(pipefd[1]);          /* Close unused write end */

    while (read(pipefd[0], read_buf, 1) > 0)
      write(STDOUT_FILENO, read_buf, 1);

    write(STDOUT_FILENO, "\n", 1);
    close(pipefd[0]);
    exit(EXIT_SUCCESS);

  } else {            /* Parent writes argv[1] to pipe */
    close(pipefd[0]);          /* Close unused read end */

    string txString (argv[1]); 
    int nbytes = txString.length();
    write(pipefd[1], txString.c_str(), nbytes);

    close(pipefd[1]);          /* Reader will see EOF */
    wait(NULL);                /* Wait for child */
    exit(EXIT_SUCCESS);
  }
}
