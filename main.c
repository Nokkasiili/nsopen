#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <magic.h>
#include <stdbool.h>
#include <unistd.h>

#define LENGTH(x) (sizeof x / sizeof x[0])

typedef struct {
  char *token;
  char *program;
  bool term;
} Rule;

#include "config.h"

void die(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);

  if (fmt[0] && fmt[strlen(fmt) - 1] == ':') {
    fputc(' ', stderr);
    perror(NULL);
  }

  exit(EXIT_FAILURE);
}

void spawn(char *command, bool needsfork) {
  if(needsfork){
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
  }

  if (!needsfork || fork() == 0) {  // hack ?
    char *exec[] = {"/bin/sh", "-c", command, NULL};
    setsid();
    execvp(((char **)exec)[0], (char **)exec);
    die("execvp %s failed:",((char**)exec)[0]);
    exit(EXIT_SUCCESS);
  }
}

void spawner(Rule mime, char *argument) {
  char *term;
  char command[256];
  if (!isatty(fileno(stdin)) && mime.term) {
    term = getenv("TERM");
    snprintf(command, sizeof(command), "%s -e \"%s\" \"%s\" ",
             term ? term : "xterm", mime.program, argument);
    spawn(command, true);
  } else {
    if (!mime.term) {
      snprintf(command, sizeof(command), "%s \"%s\"",
               mime.program, argument);
      spawn(command, true);
    } else {
      snprintf(command, sizeof(command), "%s \"%s\"", mime.program, argument);
      spawn(command, false);
    }
  }
}

int main(int argc, char *argv[]) {
  magic_t cookie;
  int i;
  cookie = magic_open(MAGIC_MIME_TYPE);

  if (argc != 2)
    die("Usage %s [PATH|URL]\n", argv[0]);
  if (cookie == NULL)
    die("error loading the magic database\n");
  if (magic_load(cookie, NULL))
    die("error loading the magic database\n");

  char *arg = argv[1];
  const char *description;

  description = magic_file(cookie, argv[1]);
  if (description != NULL) {
    for (i = 0; i < LENGTH(mimes); i++) {
      if (strncmp(description, mimes[i].token, strlen(mimes[i].token)) == 0) {
        spawner(mimes[i], arg);
        magic_close(cookie);
        return EXIT_SUCCESS;
      }
    }
  }

  magic_close(cookie);

  for (i = 0; i < LENGTH(protocols); i++) {
    if (strncmp(arg, protocols[i].token, strlen(protocols[i].token)) == 0) {
      spawner(protocols[i], arg);
      return EXIT_SUCCESS;
    }
  }
  printf("%s\n", argv[1]);  // no match

  return EXIT_SUCCESS;
}
