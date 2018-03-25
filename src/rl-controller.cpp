#include "rl-controller.h"

#include <history.h>
#include <readline.h>

#define AS_CMD_PROMPT "AS >>> "

QRlController::QRlController()
{
}

void QRlController::run()
{
  do {
    char *const line = readline(AS_CMD_PROMPT);
    if (!line || !strlen(line)) {
      free(line);
      continue;
    } else if (!strcmp(line, "exit")) {
      free(line);
      break;
    }
    add_history(line);

    emit command(line);

    /* Cleanup */
    free(line);
  } while (true);
}
