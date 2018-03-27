#include "cmd-unknown.h"

#include "cmd-help.h"

#include <QDebug>

QCmdUnknown::QCmdUnknown()
{
}

void QCmdUnknown::process()
{
  qDebug() << "Error: unknown command";

  QCmdHelp *cmd = new QCmdHelp();
  connect(cmd, &QCmdHelp::finished, this, &QCmdUnknown::done);
  cmd->start();
}
