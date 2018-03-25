#include "cmd-controller.h"

#include <history.h>
#include <readline.h>

#define AS_CMD_PROMPT "AS >>> "

QCmdController::QCmdController()
{
}

void QCmdController::onCommand(const QString &cmd)
{
  if (cmd == "help") {
    showHelp();
  } else if (cmd == "options") {
    QCmdOptions *cmd = new QCmdOptions();
    cmd->start();
  } else {
    /* Debug output */
    qDebug("Here is the unknown user input: \"%s\"", qUtf8Printable(cmd));
  }
}
