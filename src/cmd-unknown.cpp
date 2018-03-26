#include "cmd-unknown.h"

#include "cmd-help.h"

#include <QDebug>

QCmdUnknown::QCmdUnknown()
{
}

void QCmdUnknown::run()
{
  qDebug() << "Error: unknown command";

  QCmdHelp *cmd = new QCmdHelp();
  connect(cmd, &QCmdHelp::finished, this, &QCmdUnknown::finished);
  connect(cmd, &QCmdHelp::finished, cmd, &QCmdHelp::deleteLater);
  cmd->start();
}
