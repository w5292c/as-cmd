#include "cmd-unknown.h"

#include "as-debug.h"
#include "cmd-help.h"

QCmdUnknown::QCmdUnknown()
{
  qVerbose(<< "[QCmdUnknown::QCmdUnknown]" << this);
}

QCmdUnknown::~QCmdUnknown()
{
  qVerbose(<< "[QCmdUnknown::~QCmdUnknown]" << this);
}

void QCmdUnknown::process()
{
  qDebug() << "Error: unknown command";

  QCmdHelp *cmd = new QCmdHelp();
  connect(cmd, &QCmdHelp::finished, this, &QCmdUnknown::done);
  cmd->start();
}
