/*
 * MIT License
 *
 * Copyright (c) 2018 Alexander Chumakov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "cmd-controller.h"

#include "as-debug.h"
#include "cmd-help.h"
#include "cmd-options.h"
#include "cmd-unknown.h"
#include "cmd-verbose.h"
#include "cmd-sync-key.h"
#include "rl-controller.h"
#include "cmd-folder-sync.h"
#include "cmd-collection-id.h"

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
  } else if (cmd == "collection-id") {
    command = new QCmdCollectionId(true);
  } else if (cmd.startsWith("collection-id ")) {
    const int value = cmd.mid(14).toInt();
    command = new QCmdCollectionId(false, value);
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
