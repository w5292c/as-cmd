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
#include "cmd-sign.h"
#include "cmd-sync.h"
#include "cmd-help.h"
#include "cmd-prop.h"
#include "cmd-test.h"
#include "cmd-verify.h"
#include "cmd-options.h"
#include "cmd-unknown.h"
#include "cmd-verbose.h"
#include "rl-controller.h"
#include "cmd-folder-sync.h"

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
  } else if (cmd == "sign") {
    command = new QCmdSign();
  } else if (cmd == "sync") {
    command = new QCmdSync();
  } else if (cmd == "folder-sync") {
    command = new QCmdFolderSync();
  } else if (cmd == "verbose") {
    command = new QCmdVerbose(true);
  } else if (cmd.startsWith("verbose ")) {
    const bool on = (cmd.mid(8) == "on");
    command = new QCmdVerbose(false, on);
  } else if (cmd == "props") {
    command = new QCmdProp(true);
  } else if (cmd == "verify") {
    command = new QCmdVerify();
  } else if (cmd.startsWith("set ") || cmd.startsWith("get ")) {
    const QString &args = cmd.mid(4);
    if (cmd.startsWith("get ")) {
      command = new QCmdProp(false, args);
    } else {
      const int nameEndIndex = args.indexOf(' ');
      if (-1 != nameEndIndex) {
        const QString &name = args.mid(0, nameEndIndex);
        const QString &value = args.mid(nameEndIndex + 1);
        command = new QCmdProp(false, name, false, value);
      } else {
        command = new QCmdProp(false, args, false, QString::null);
      }
    }
  } else if (cmd == "test") {
    command = new QCmdTest();
  }

  if (!command) {
    command = new QCmdUnknown();
  }

  connect(command, &QCmdBase::finished, mRlController, &QRlController::onCommandDone);
  command->start();
}
