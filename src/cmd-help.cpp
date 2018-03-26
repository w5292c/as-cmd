#include "cmd-help.h"

#include <QDebug>

QCmdHelp::QCmdHelp()
{
}

void QCmdHelp::run()
{
  qDebug() << ">>> help - Show help";
  qDebug() << ">>> exit - Exit the application";

  emit finished();
}
