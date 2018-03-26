#include "cmd-controller.h"

#include "cmd-help.h"
#include "cmd-options.h"
#include "cmd-unknown.h"
#include "rl-controller.h"

#include <QDebug>
#include <history.h>
#include <readline.h>

#define AS_CMD_PROMPT "AS >>> "

QCmdController::QCmdController(QRlController *rl) : mRlController(rl)
{
}

void QCmdController::onCommand(const QString &cmd)
{
  QCmdBase *command = NULL;

  if (cmd == "help") {
    command = new QCmdHelp();
  } else if (cmd == "options") {
    command = new QCmdOptions();
  } else {
    command = new QCmdUnknown();
  }

  if (command) {
    connect(command, &QCmdBase::finished, mRlController, &QRlController::onCommandDone);
    command->start();
  } else {
    qDebug("Here is the unknown user input: \"%s\"", qUtf8Printable(cmd));
  }
}
