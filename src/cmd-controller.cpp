#include "cmd-controller.h"

#include "as-debug.h"
#include "cmd-help.h"
#include "cmd-options.h"
#include "cmd-unknown.h"
#include "cmd-verbose.h"
#include "cmd-sync-key.h"
#include "rl-controller.h"
#include "cmd-folder-sync.h"

#include <history.h>
#include <readline.h>

#define AS_CMD_PROMPT "AS >>> "

QCmdController::QCmdController(QRlController *rl) : mRlController(rl)
{
  qVerbose(<< "[QCmdController::QCmdController]" << this);
}

QCmdController::~QCmdController()
{
  qVerbose(<< "[QCmdController::~QCmdController]" << this);
}

void QCmdController::onCommand(const QString &cmd)
{
  QCmdBase *command = NULL;

  if (cmd == "help") {
    command = new QCmdHelp();
  } else if (cmd == "options") {
    command = new QCmdOptions();
  } else if (cmd == "folder-sync") {
    command = new QCmdFolderSync();
  } else if (cmd == "verbose") {
    command = new QCmdVerbose(true);
  } else if (cmd.startsWith("verbose ")) {
    const bool on = (cmd.mid(8) == "on");
    command = new QCmdVerbose(false, on);
  } else if (cmd == "sync-key") {
    command = new QCmdSyncKey(true);
  } else if (cmd.startsWith("sync-key ")) {
    const int value = cmd.mid(9).toInt();
    command = new QCmdSyncKey(false, value);
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
