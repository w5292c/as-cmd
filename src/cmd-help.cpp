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

#include "cmd-help.h"

#include "as-debug.h"

QCmdHelp::QCmdHelp()
{
  qVerbose(<< "[QCmdHelp::QCmdHelp]" << this);
}

QCmdHelp::~QCmdHelp()
{
  qVerbose(<< "[QCmdHelp::~QCmdHelp]" << this);
}

void QCmdHelp::process()
{
  qDebug() << ">>> help - Show help";
  qDebug() << ">>> exit - Exit the application";
  qDebug() << ">>> verbose [<on>|<off>] - Show or enable/disable verbose output";
  qDebug() << ">>> options - Send 'OPTIONS' request";
  qDebug() << ">>> folder-sync - Send FolderSync command";
  qDebug() << ">>> get <name> - Get the value of property <name>";
  qDebug() << ">>> set <name> - Remove property <name>";
  qDebug() << ">>> set <name> <value> - Sete property <name> to <value>";
  qDebug() << ">>> set <name>< > - Set property <name> to empty string";
  qDebug() << ">>> props - Show the names of the currenltly existing properties";
  qDebug() << ">>> sync ('syncKey', 'collectionId', 'windowSize', 'deletesAsMoves', 'getChanges') - Send 'sync' command with parameters";

  emit done();
}
