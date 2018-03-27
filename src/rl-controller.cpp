#include "rl-controller.h"

#include "as-debug.h"

#include <history.h>
#include <readline.h>

#define AS_CMD_PROMPT "AS >>> "

QRlController::QRlController()
{
  qVerbose(<< "[QRlController::QRlController]" << this);
}

QRlController::~QRlController()
{
  qVerbose(<< "[QRlController::~QRlController]" << this);
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

    exec();
  } while (true);
}

void QRlController::onCommandDone()
{
  exit(0);
}
