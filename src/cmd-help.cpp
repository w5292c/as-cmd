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
  qDebug() << ">>> options - Send 'OPTIONS' request";
  qDebug() << ">>> verbose [<on>|<off>] - Show or enable/disable verbose output";

  emit done();
}
